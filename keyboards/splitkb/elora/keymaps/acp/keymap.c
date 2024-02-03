/* Copyright 2023 splitkb.com <support@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum layers {
    _BASE = 0,
    _LAYER_1,
    _LAYER_2,
    _LAYER_3,
};

// Aliases for readability
#define BASE   DF(_BASE)
#define LAYER_1  DF(_LAYER_1)
#define LAYER_2  DF(_LAYER_2)
#define LAYER_3  DF(_LAYER_3)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)
#define ALT_SPC  LALT_T(KC_SPC)

#define UNDO  LCTL(KC_Z)
#define CUT   LCTL(KC_X)
#define COPY  LCTL(KC_C)
#define PASTE LCTL(KC_V)

// ChromeOS Screenshot.
#define SCREENS LSFT(LCTL(LGUI(KC_F5)))
// ChromeOS Windows picker.
#define WDOWS   LGUI(KC_F5)
// ChromeOS Lock.
#define LOCK    LGUI(KC_L)
// ChromeOS Switch user.
#define SWITCH LCA(KC_DOT)

// Start of advanced tap-dance setup:
// (tap, double-tap, hold) as per https://docs.qmk.fm/#/feature_tap_dance?id=example-4.
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap dance enums
enum {
    OP_BRA,   // Open parenthesis on single tap, open curly bracket on hold, open square bracket on double-tap.
    CL_BRA,   // Close of OP_BRA.
    DA_ALTGR, // Dead accent grave on single tap, dead accent aigu on double-tap, dead circumflex on tap and hold, AltGr on hold.
    MEDIA,    // Play/pause on tap, Next on double-tap, Back on tap and hold.
};

td_state_t cur_dance(tap_dance_state_t *state);

void open_brackets_finished(tap_dance_state_t *state, void *user_data);
void open_brackets_reset(tap_dance_state_t *state, void *user_data);
void close_brackets_finished(tap_dance_state_t *state, void *user_data);
void close_brackets_reset(tap_dance_state_t *state, void *user_data);
void dead_accents_altgr_finished(tap_dance_state_t *state, void *user_data);
void dead_accents_altgr_reset(tap_dance_state_t *state, void *user_data);

// End of tap-dance setup.

enum custom_keycodes {
    MA_DEAD_GRAVE = SAFE_RANGE,
    MA_DEAD_AIGU,
    MA_DEAD_CIRC,
    MA_ALTGR,
};


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: BASE
 *
 * ,-------------------------------------------.      ,------.  ,------.      ,-------------------------------------------.
 * | ` ~    |   1  |   2  |   3  |   4  |   5  |      |      |  |      |      |   6  |   7  |   8  |   9  |   0  |  Esc   |
 * |--------+------+------+------+------+------|      |------|  |------|      |------+------+------+------+------+--------|
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |      |      |  |      |      |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
 * |--------+------+------+------+------+------|      |------|  |------|      |------+------+------+------+------+--------|
 * |Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |      |      |  |      |      |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------+------+------|  |------|------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | - _  | ({[  |  |  ]}) |  = + |   N  |   M  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | LGUI | LCTL | MO(1)| Alt/ | Pause|  | RCTL | Enter| MO(2)| AltGr| RGUI |
 *                        |      |      |      |  Spc |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 *
 * ,----------------------------.      ,------.                 ,----------------------------.      ,------.
 * | Prev | Next | Pause | Stop |      | Mute |                 | Prev | Next | Pause | Stop |      | Mute |
 * `----------------------------'      `------'                 `----------------------------'      '------'
 */
    [_BASE] = LAYOUT_myr(
      KC_GRV  , KC_1 ,  KC_2   ,  KC_3  ,   KC_4 ,   KC_5 ,         _______,     _______,          KC_6 ,  KC_7 ,  KC_8 ,   KC_9 ,  KC_0 , KC_GRV,
      KC_ESC  , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,         _______,     _______,          KC_Y ,  KC_U ,  KC_I ,   KC_O ,  KC_P , KC_BSPC,
      KC_TAB  , KC_A ,  KC_S   ,  KC_D  ,   KC_F ,   KC_G ,         _______,     _______,          KC_H ,  KC_J ,  KC_K ,   KC_L ,KC_SCLN,KC_QUOT,
      KC_LSFT , KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B , KC_MINS,TD(OP_BRA),TD(CL_BRA), KC_EQL, KC_N ,  KC_M ,KC_COMM, KC_DOT ,KC_SLSH, KC_RSFT,
                                 KC_LGUI , KC_LCTL, MO(1) , ALT_SPC ,TD(MEDIA),     KC_RCTL    , KC_ENT ,MO(2),TD(DA_ALTGR), KC_RGUI,

      _______, _______, _______, _______,    KC_MUTE,                            _______, _______, _______, _______,    KC_BTN1
    ),

/*
 * Layer 1
 *
 * ,-------------------------------------------.      ,------.  ,------.      ,-------------------------------------------.
 * | TRNS   |   1  |   2  |   3  |   4  |   5  |      |      |  |      |      |   6  |   7  |   8  |   9  |   0  |  TRNS  |
 * |--------+------+------+------+------+------|      |------|  |------|      |------+------+------+------+------+--------|
 * | TRNS   |   1  |   2  |   3  |   4  |   5  |      |      |  |      |      |   6  |   7  |   8  |   9  |   0  |  TRNS  |
 * |--------+------+------+------+------+------|      |------|  |------|      |------+------+------+------+------+--------|
 * | TRNS   |      |      |      |      |      |      |      |  |      |      |   ←  |   ↓  |  ↑   |   →  |      |  TRNS  |
 * |--------+------+------+------+------+------+------+------|  |------|------+------+------+------+------+------+--------|
 * | TRNS   | UNDO |  CUT | COPY | PASTE|      | TRNS | TRNS |  | TRNS |      |      |      |      |      |      |  TRNS  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | TRNS | TRNS | TRNS | TRNS | TRNS |  | TRNS | TRNS |MO(3) | TRNS | TRNS |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 *
 * ,----------------------------.      ,------.                 ,----------------------------.      ,------.
 * | Prev | Next | Pause | Stop |      | Mute |                 | Prev | Next | Pause | Stop |      | Mute |
 * `----------------------------'      `------'                 `----------------------------'      '------'
 */
    [_LAYER_1] = LAYOUT_myr(
      KC_TRNS , KC_1 ,  KC_2   ,  KC_3  ,   KC_4 ,   KC_5 ,         _______,     _______,          KC_6 ,  KC_7 ,  KC_8 ,   KC_9 ,  KC_0 , KC_TRNS,
      KC_TRNS , KC_1 ,  KC_2   ,  KC_3  ,   KC_4 ,   KC_5 ,         _______,     _______,          KC_6 ,  KC_7 ,  KC_8 ,   KC_9 ,  KC_0 , KC_TRNS,
      KC_TRNS ,_______,_______ ,_______ , _______,_______ ,         _______,     _______,        KC_LEFT,KC_DOWN, KC_UP ,KC_RGHT ,_______,KC_TRNS,
      KC_TRNS , UNDO ,  CUT    ,  COPY  ,  PASTE ,_______, KC_TRNS,KC_TRNS,     KC_TRNS, KC_TRNS,_______,_______,_______,_______ ,_______, KC_TRNS,
                                 KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,     KC_TRNS       , KC_TRNS ,MO(3),KC_TRNS, KC_TRNS,

      _______, _______, _______, _______,    KC_TRNS,                            _______, _______, _______, _______,    _______
    ),


/*
 * Layer 2
 *
 * ,-------------------------------------------.      ,------.  ,------.      ,-------------------------------------------.
 * | TRNS   |  F1  |  F2  |  F3  |  F4  |  F5  |      |      |  |      |      |  F6  |  F7  |  F8  |  F9  | F10  |  F11   |
 * |--------+------+------+------+------+------|      |------|  |------|      |------+------+------+------+------+--------|
 * | TRNS   |   !  |   @  |   #  |   $  |   %  |      |      |  |      |      |   ^  |   &  |   *  |   +  |   |  |  F12   |
 * |--------+------+------+------+------+------|      |------|  |------|      |------+------+------+------+------+--------|
 * | TRNS   |      |      |      |      |      |      |      |  |      |      |   (  |   )  | - _  |   {  |   }  |  ` ~   |
 * |--------+------+------+------+------+------+------+------|  |------|------+------+------+------+------+------+--------|
 * | TRNS   |      |      |      |      |      | TRNS | TRNS |  | TRNS | TRNS | [ {  | } ]  | = +  |      | \ |  |  TRNS  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | TRNS | TRNS | MO(3)| TRNS | TRNS |  | TRNS | TRNS | TRNS | TRNS | TRNS |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 *
 * ,----------------------------.      ,------.                 ,----------------------------.      ,------.
 * | Prev | Next | Pause | Stop |      | Mute |                 | Prev | Next | Pause | Stop |      | Mute |
 * `----------------------------'      `------'                 `----------------------------'      '------'
 */
    [_LAYER_2] = LAYOUT_myr(
      KC_TRNS , KC_F1,  KC_F2  ,  KC_F3 ,   KC_F4,   KC_F5,         _______,     _______,          KC_F6,  KC_F7,  KC_F8,   KC_F9,KC_F10 , KC_F11,
      KC_TRNS , KC_1 ,  KC_2   ,  KC_3  ,   KC_4 ,   KC_5 ,         _______,     _______,        KC_CIRC,KC_AMPR,KC_ASTR, KC_PLUS,KC_PIPE, KC_F12,
      KC_TRNS ,_______,_______ ,_______ , _______,_______ ,         _______,     _______,        KC_LPRN,KC_RPRN,KC_MINS ,KC_LCBR,KC_RCBR, KC_GRV,
      KC_TRNS , UNDO ,  CUT    ,  COPY  ,  PASTE ,_______, KC_TRNS,KC_TRNS,     KC_TRNS, KC_TRNS,KC_LBRC,KC_RBRC, KC_EQL ,_______ ,KC_BSLS, KC_TRNS,
                                 KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,     KC_TRNS       , KC_TRNS ,KC_TRNS,KC_TRNS, KC_TRNS,

      _______, _______, _______, _______,    KC_TRNS,                            _______, _______, _______, _______,    _______
    ),


/*
 * Layer 3
 *
 * ,-------------------------------------------.      ,------.  ,------.      ,-------------------------------------------.
 * | TRNS   | TRNS | TRNS | TRNS | TRNS | TRNS |      |      |  |      |      | TRNS | TRNS | TRNS | TRNS | TRNS |  TRNS  |
 * |--------+------+------+------+------+------|      |------|  |------|      |------+------+------+------+------+--------|
 * | Reset  |      |      |      |      | Vol+ |      |      |  |      |      | Prev | Play | Next |      |      |  TRNS  |
 * |--------+------+------+------+------+------|      |------|  |------|      |------+------+------+------+------+--------|
 * | TRNS   | Hue+ | Sat+ |Brght+|RGB Tg| Vol- |      |      |  |      |      | Home |PgDown| PgUp | End  |      |  TRNS  |
 * |--------+------+------+------+------+------+------+------|  |------|------+------+------+------+------+------+--------|
 * | TRNS   | Hue- | Sat- |Brght-| RGB+ | Mute | TRNS | TRNS |  | TRNS | TRNS |ScrenS|Wndows| Lock |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | TRNS | TRNS | TRNS | TRNS | TRNS |  | TRNS | TRNS | TRNS |Switch| TRNS |
 *                        |      |      |      |      |      |  |      |      |      | User |      |
 *                        `----------------------------------'  `----------------------------------'
 *
 * ,----------------------------.      ,------.                 ,----------------------------.      ,------.
 * | Prev | Next | Pause | Stop |      | Mute |                 | Prev | Next | Pause | Stop |      | Mute |
 * `----------------------------'      `------'                 `----------------------------'      '------'
 */
    [_LAYER_3] = LAYOUT_myr(
      KC_TRNS ,KC_TRNS,KC_TRNS ,KC_TRNS ,KC_TRNS , KC_TRNS,         _______,     _______,        KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS,
      QK_BOOT ,_______,_______ ,_______ , _______, KC_VOLU,         _______,     _______,        KC_MPRV,KC_MPLY,KC_MNXT, _______,_______, KC_TRNS,
      KC_TRNS ,RGB_HUI,RGB_SAI ,RGB_VAI , RGB_TOG, KC_VOLD,         _______,     _______,        KC_HOME,KC_PGDN,KC_PGUP, KC_END ,_______, KC_TRNS,
      KC_TRNS ,RGB_HUD,RGB_SAD ,RGB_VAD , RGB_MOD,KC_MUTE, KC_TRNS,KC_TRNS,     KC_TRNS, KC_TRNS,SCREENS, WDOWS , LOCK  ,_______,_______,_______,
                                 KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,     KC_TRNS       , KC_TRNS ,KC_TRNS,SWITCH , KC_TRNS,

      _______, _______, _______, _______,    KC_TRNS,                            _______, _______, _______, _______,    _______
    ),


// /*
//  * Layer template - LAYOUT
//  *
//  * ,-------------------------------------------.      ,------.  ,------.      ,-------------------------------------------.
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|      |------|  |------|      |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|      |------|  |------|      |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+------+------|  |------|------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),

// /*
//  * Layer template - LAYOUT_myr
//  *
//  * ,-------------------------------------------.      ,------.  ,------.      ,-------------------------------------------.
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|      |------|  |------|      |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|      |------|  |------|      |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+------+------|  |------|------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  *
//  * ,-----------------------------.      ,------.                ,---------------------------.      ,------.
//  * |        |      |      |      |      |      |                |      |      |      |      |      |      |
//  * `-----------------------------'      `------'                `---------------------------'      '------'
//  */
//     [_LAYERINDEX] = LAYOUT_myr(
//       _______, _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//
//       _______, _______, _______, _______,          _______,                   _______, _______, _______, _______,          _______
//     ),
};

//#ifdef ENCODER_ENABLE
//bool encoder_update_kb(uint8_t index, bool clockwise) {
//    if (!encoder_update_user(index, clockwise)) {
//        return false;
//    }
//    // Myriad
//    // Volume control
//    if (clockwise) {
//        tap_code(KC_VOLU);
//    } else {
//        tap_code(KC_VOLD);
//    }
//    return true;
//}
//#endif


// Advanced tap-dance codification as per: https://docs.qmk.fm/#/feature_tap_dance?id=example-4

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

// OP_BRA advanced tap-dance setup.
static td_tap_t open_brackets_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void open_brackets_finished(tap_dance_state_t *state, void *user_data) {
    open_brackets_tap_state.state = cur_dance(state);
    switch (open_brackets_tap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_LSFT); register_code(KC_9); break;
        case TD_SINGLE_HOLD: register_code(KC_LSFT); register_code(KC_LBRC); break;
        case TD_DOUBLE_TAP: register_code(KC_LBRC); break;
        default: break;
    }
}

void open_brackets_reset(tap_dance_state_t *state, void *user_data) {
    switch (open_brackets_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_9); unregister_code(KC_LSFT); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LSFT); unregister_code(KC_LBRC); break;
        case TD_DOUBLE_TAP: unregister_code(KC_LBRC); break;
        default: break;
    }
    open_brackets_tap_state.state = TD_NONE;
}

// CL_BRA advanced tap-dance setup.
static td_tap_t close_brackets_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void close_brackets_finished(tap_dance_state_t *state, void *user_data) {
    close_brackets_tap_state.state = cur_dance(state);
    switch (close_brackets_tap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_LSFT); register_code(KC_0); break;
        case TD_SINGLE_HOLD: register_code(KC_LSFT); register_code(KC_RBRC); break;
        case TD_DOUBLE_TAP: register_code(KC_RBRC); break;
        default: break;
    }
}

void close_brackets_reset(tap_dance_state_t *state, void *user_data) {
    switch (close_brackets_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_0); unregister_code(KC_LSFT); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LSFT); unregister_code(KC_RBRC); break;
        case TD_DOUBLE_TAP: unregister_code(KC_RBRC); break;
        default: break;
    }
    close_brackets_tap_state.state = TD_NONE;
}

// DA_ALTGR advanced tap-dance setup.
static td_tap_t dead_accents_altgr_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void dead_accents_altgr_finished(tap_dance_state_t *state, void *user_data) {
    dead_accents_altgr_tap_state.state = cur_dance(state);
    switch (dead_accents_altgr_tap_state.state) {
        case TD_SINGLE_TAP:
	    register_code(KC_RALT);
	    tap_code_delay(KC_GRV, 10);
	    unregister_code(KC_RALT);
	    break;
        case TD_SINGLE_HOLD: register_code(KC_RALT); break;
        case TD_DOUBLE_TAP:
	    register_code(KC_RALT);
	    tap_code_delay(KC_QUOT, 10);
	    unregister_code(KC_RALT);
	    break;
        case TD_DOUBLE_HOLD:
	    register_code(KC_RALT);
	    tap_code_delay(KC_6, 10);
	    unregister_code(KC_RALT);
	    break;
        default: break;
    }
}

void dead_accents_altgr_reset(tap_dance_state_t *state, void *user_data) {
    switch (dead_accents_altgr_tap_state.state) {
        case TD_SINGLE_HOLD: unregister_code(KC_RALT); break;
        default: break;
    }
    dead_accents_altgr_tap_state.state = TD_NONE;
}

// MEDIA advanced tap-dance setup.
static td_tap_t media_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void media_finished(tap_dance_state_t *state, void *user_data) {
    media_tap_state.state = cur_dance(state);
    switch (media_tap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_MPLY); break;
        case TD_SINGLE_HOLD: register_code(KC_MPRV); break;
        case TD_DOUBLE_TAP: register_code(KC_MNXT); break;
        default: break;
    }
}

void media_reset(tap_dance_state_t *state, void *user_data) {
    switch (media_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_MPLY); break;
        case TD_SINGLE_HOLD: unregister_code(KC_MPRV); break;
        case TD_DOUBLE_TAP: unregister_code(KC_MNXT); break;
        default: break;
    }
    media_tap_state.state = TD_NONE;
}


tap_dance_action_t tap_dance_actions[] = {
    [OP_BRA] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, open_brackets_finished, open_brackets_reset),
    [CL_BRA] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, close_brackets_finished, close_brackets_reset),
    [DA_ALTGR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dead_accents_altgr_finished, dead_accents_altgr_reset),
    [MEDIA] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, media_finished, media_reset)
};

//// Add support for some of the custom keycodes (macros) above.
//bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//    switch (keycode) {
//    case MA_DEAD_GRAVE:
//        if (record->event.pressed) {
//	    SS_DOWN(KC_RALT);
//	    SS_TAP(KC_GRV);
//            SS_DELAY(10);
//	    SS_UP(KC_RALT);
//        }
//        break;
//    case MA_DEAD_AIGU:
//        if (record->event.pressed) {
//	    SS_DOWN(KC_RALT);
//	    SS_TAP(KC_QUOT);
//            SS_DELAY(10);
//	    SS_UP(KC_RALT);
//        }
//        break;
//    case MA_DEAD_CIRC:
//        if (record->event.pressed) {
//	    SS_DOWN(KC_RALT);
//	    SS_TAP(KC_6);
//            SS_DELAY(10);
//	    SS_UP(KC_RALT);
//        }
//        break;
//    }
//    return true;
//};
