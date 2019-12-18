#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int py; } ;
typedef  TYPE_1__ touchPosition ;
struct TYPE_7__ {int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;
typedef  TYPE_2__ circlePosition ;

/* Variables and functions */
 int /*<<< orphan*/  BIT64_CLEAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIT64_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMD_EVENT_QUIT ; 
 int KEY_A ; 
 int KEY_B ; 
 int KEY_DDOWN ; 
 int KEY_DLEFT ; 
 int KEY_DRIGHT ; 
 int KEY_DUP ; 
 int KEY_L ; 
 int KEY_R ; 
 int KEY_SELECT ; 
 int KEY_START ; 
 int KEY_TOUCH ; 
 int KEY_X ; 
 int KEY_Y ; 
 int KEY_ZL ; 
 int KEY_ZR ; 
 int /*<<< orphan*/  RARCH_MENU_TOGGLE ; 
 size_t RETRO_DEVICE_ID_ANALOG_X ; 
 size_t RETRO_DEVICE_ID_ANALOG_Y ; 
 int RETRO_DEVICE_ID_JOYPAD_A ; 
 int RETRO_DEVICE_ID_JOYPAD_B ; 
 int RETRO_DEVICE_ID_JOYPAD_DOWN ; 
 int RETRO_DEVICE_ID_JOYPAD_L ; 
 int RETRO_DEVICE_ID_JOYPAD_L2 ; 
 int RETRO_DEVICE_ID_JOYPAD_LEFT ; 
 int RETRO_DEVICE_ID_JOYPAD_R ; 
 int RETRO_DEVICE_ID_JOYPAD_R2 ; 
 int RETRO_DEVICE_ID_JOYPAD_RIGHT ; 
 int RETRO_DEVICE_ID_JOYPAD_SELECT ; 
 int RETRO_DEVICE_ID_JOYPAD_START ; 
 int RETRO_DEVICE_ID_JOYPAD_UP ; 
 int RETRO_DEVICE_ID_JOYPAD_X ; 
 int RETRO_DEVICE_ID_JOYPAD_Y ; 
 size_t RETRO_DEVICE_INDEX_ANALOG_LEFT ; 
 size_t RETRO_DEVICE_INDEX_ANALOG_RIGHT ; 
 int /*<<< orphan*/ *** analog_state ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctr_joypad_fix_range (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hidCircleRead (TYPE_2__*) ; 
 int hidKeysHeld () ; 
 int /*<<< orphan*/  hidScanInput () ; 
 int /*<<< orphan*/  hidTouchRead (TYPE_1__*) ; 
 int /*<<< orphan*/  irrstCstickRead (TYPE_2__*) ; 
 int /*<<< orphan*/  lifecycle_state ; 
 int pad_state ; 

__attribute__((used)) static void ctr_joypad_poll(void)
{
   uint32_t state_tmp;
   circlePosition state_tmp_left_analog, state_tmp_right_analog;
   touchPosition state_tmp_touch;

   hidScanInput();

   state_tmp = hidKeysHeld();
   hidCircleRead(&state_tmp_left_analog);
   irrstCstickRead(&state_tmp_right_analog);
   hidTouchRead(&state_tmp_touch);

   pad_state = 0;
   pad_state |= (state_tmp & KEY_DLEFT) ? (1 << RETRO_DEVICE_ID_JOYPAD_LEFT) : 0;
   pad_state |= (state_tmp & KEY_DDOWN) ? (1 << RETRO_DEVICE_ID_JOYPAD_DOWN) : 0;
   pad_state |= (state_tmp & KEY_DRIGHT) ? (1 << RETRO_DEVICE_ID_JOYPAD_RIGHT) : 0;
   pad_state |= (state_tmp & KEY_DUP) ? (1 << RETRO_DEVICE_ID_JOYPAD_UP) : 0;
   pad_state |= (state_tmp & KEY_START) ? (1 << RETRO_DEVICE_ID_JOYPAD_START) : 0;
   pad_state |= (state_tmp & KEY_SELECT) ? (1 << RETRO_DEVICE_ID_JOYPAD_SELECT) : 0;
   pad_state |= (state_tmp & KEY_X) ? (1 << RETRO_DEVICE_ID_JOYPAD_X) : 0;
   pad_state |= (state_tmp & KEY_Y) ? (1 << RETRO_DEVICE_ID_JOYPAD_Y) : 0;
   pad_state |= (state_tmp & KEY_B) ? (1 << RETRO_DEVICE_ID_JOYPAD_B) : 0;
   pad_state |= (state_tmp & KEY_A) ? (1 << RETRO_DEVICE_ID_JOYPAD_A) : 0;
   pad_state |= (state_tmp & KEY_R) ? (1 << RETRO_DEVICE_ID_JOYPAD_R) : 0;
   pad_state |= (state_tmp & KEY_L) ? (1 << RETRO_DEVICE_ID_JOYPAD_L) : 0;
   pad_state |= (state_tmp & KEY_ZR) ? (1 << RETRO_DEVICE_ID_JOYPAD_R2) : 0;
   pad_state |= (state_tmp & KEY_ZL) ? (1 << RETRO_DEVICE_ID_JOYPAD_L2) : 0;

   analog_state[0][RETRO_DEVICE_INDEX_ANALOG_LEFT] [RETRO_DEVICE_ID_ANALOG_X]  =  ctr_joypad_fix_range(state_tmp_left_analog.dx);
   analog_state[0][RETRO_DEVICE_INDEX_ANALOG_LEFT] [RETRO_DEVICE_ID_ANALOG_Y]  = -ctr_joypad_fix_range(state_tmp_left_analog.dy);
   analog_state[0][RETRO_DEVICE_INDEX_ANALOG_RIGHT] [RETRO_DEVICE_ID_ANALOG_X] =  ctr_joypad_fix_range(state_tmp_right_analog.dx);
   analog_state[0][RETRO_DEVICE_INDEX_ANALOG_RIGHT] [RETRO_DEVICE_ID_ANALOG_Y] = -ctr_joypad_fix_range(state_tmp_right_analog.dy);

   BIT64_CLEAR(lifecycle_state, RARCH_MENU_TOGGLE);

   if((state_tmp & KEY_TOUCH) && (state_tmp_touch.py > 120))
      BIT64_SET(lifecycle_state, RARCH_MENU_TOGGLE);

   /* panic button */
   if((state_tmp & KEY_START) &&
         (state_tmp & KEY_SELECT) &&
         (state_tmp & KEY_L) &&
         (state_tmp & KEY_R))
      command_event(CMD_EVENT_QUIT, NULL);

}