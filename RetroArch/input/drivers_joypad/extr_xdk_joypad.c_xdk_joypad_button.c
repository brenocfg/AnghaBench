#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_4__ {int wButtons; int /*<<< orphan*/ * bAnalogButtons; } ;
struct TYPE_5__ {TYPE_1__ Gamepad; } ;
struct TYPE_6__ {TYPE_2__ xstate; } ;

/* Variables and functions */
 unsigned int DEFAULT_MAX_PADS ; 
 unsigned int GET_HAT_DIR (int) ; 
#define  HAT_DOWN_MASK 143 
#define  HAT_LEFT_MASK 142 
#define  HAT_RIGHT_MASK 141 
#define  HAT_UP_MASK 140 
#define  RETRO_DEVICE_ID_JOYPAD_A 139 
#define  RETRO_DEVICE_ID_JOYPAD_B 138 
#define  RETRO_DEVICE_ID_JOYPAD_L 137 
#define  RETRO_DEVICE_ID_JOYPAD_L2 136 
#define  RETRO_DEVICE_ID_JOYPAD_L3 135 
#define  RETRO_DEVICE_ID_JOYPAD_R 134 
#define  RETRO_DEVICE_ID_JOYPAD_R2 133 
#define  RETRO_DEVICE_ID_JOYPAD_R3 132 
#define  RETRO_DEVICE_ID_JOYPAD_SELECT 131 
#define  RETRO_DEVICE_ID_JOYPAD_START 130 
#define  RETRO_DEVICE_ID_JOYPAD_X 129 
#define  RETRO_DEVICE_ID_JOYPAD_Y 128 
 size_t XINPUT_GAMEPAD_A ; 
 size_t XINPUT_GAMEPAD_B ; 
 int XINPUT_GAMEPAD_BACK ; 
 size_t XINPUT_GAMEPAD_BLACK ; 
 int XINPUT_GAMEPAD_DPAD_DOWN ; 
 int XINPUT_GAMEPAD_DPAD_LEFT ; 
 int XINPUT_GAMEPAD_DPAD_RIGHT ; 
 int XINPUT_GAMEPAD_DPAD_UP ; 
 int XINPUT_GAMEPAD_LEFT_THUMB ; 
 size_t XINPUT_GAMEPAD_LEFT_TRIGGER ; 
 int /*<<< orphan*/  XINPUT_GAMEPAD_MAX_CROSSTALK ; 
 int XINPUT_GAMEPAD_RIGHT_THUMB ; 
 size_t XINPUT_GAMEPAD_RIGHT_TRIGGER ; 
 int XINPUT_GAMEPAD_START ; 
 size_t XINPUT_GAMEPAD_WHITE ; 
 size_t XINPUT_GAMEPAD_X ; 
 size_t XINPUT_GAMEPAD_Y ; 
 int* button_index_to_bitmap_code ; 
 TYPE_3__* g_xinput_states ; 

__attribute__((used)) static bool xdk_joypad_button(unsigned port_num, uint16_t joykey)
{
   uint16_t btn_word  = 0;
   unsigned hat_dir   = 0;

   if (port_num >= DEFAULT_MAX_PADS)
      return false;

   btn_word = g_xinput_states[port_num].xstate.Gamepad.wButtons;
   hat_dir  = GET_HAT_DIR(joykey);

   if (hat_dir)
   {
      switch (hat_dir)
      {
         case HAT_UP_MASK:
            return btn_word & XINPUT_GAMEPAD_DPAD_UP;
         case HAT_DOWN_MASK:
            return btn_word & XINPUT_GAMEPAD_DPAD_DOWN;
         case HAT_LEFT_MASK:
            return btn_word & XINPUT_GAMEPAD_DPAD_LEFT;
         case HAT_RIGHT_MASK:
            return btn_word & XINPUT_GAMEPAD_DPAD_RIGHT;
      }

      return false; /* hat requested and no hat button down. */
   }

#ifdef _XBOX1
   switch (joykey)
   {
      case RETRO_DEVICE_ID_JOYPAD_A:
         return (g_xinput_states[port_num].xstate.Gamepad.bAnalogButtons[XINPUT_GAMEPAD_B] > XINPUT_GAMEPAD_MAX_CROSSTALK);
      case RETRO_DEVICE_ID_JOYPAD_B:
         return (g_xinput_states[port_num].xstate.Gamepad.bAnalogButtons[XINPUT_GAMEPAD_A] > XINPUT_GAMEPAD_MAX_CROSSTALK);
      case RETRO_DEVICE_ID_JOYPAD_Y:
         return (g_xinput_states[port_num].xstate.Gamepad.bAnalogButtons[XINPUT_GAMEPAD_X] > XINPUT_GAMEPAD_MAX_CROSSTALK);
      case RETRO_DEVICE_ID_JOYPAD_X:
         return (g_xinput_states[port_num].xstate.Gamepad.bAnalogButtons[XINPUT_GAMEPAD_Y] > XINPUT_GAMEPAD_MAX_CROSSTALK);
      case RETRO_DEVICE_ID_JOYPAD_START:
         return (g_xinput_states[port_num].xstate.Gamepad.wButtons & XINPUT_GAMEPAD_START);
      case RETRO_DEVICE_ID_JOYPAD_SELECT:
         return (g_xinput_states[port_num].xstate.Gamepad.wButtons & XINPUT_GAMEPAD_BACK);
      case RETRO_DEVICE_ID_JOYPAD_L3:
         return (g_xinput_states[port_num].xstate.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB);
      case RETRO_DEVICE_ID_JOYPAD_R3:
         return (g_xinput_states[port_num].xstate.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB);
      case RETRO_DEVICE_ID_JOYPAD_L2:
         return (g_xinput_states[port_num].xstate.Gamepad.bAnalogButtons[XINPUT_GAMEPAD_WHITE] > XINPUT_GAMEPAD_MAX_CROSSTALK);
      case RETRO_DEVICE_ID_JOYPAD_R2:
         return (g_xinput_states[port_num].xstate.Gamepad.bAnalogButtons[XINPUT_GAMEPAD_BLACK] > XINPUT_GAMEPAD_MAX_CROSSTALK);
      case RETRO_DEVICE_ID_JOYPAD_L:
         return (g_xinput_states[port_num].xstate.Gamepad.bAnalogButtons[XINPUT_GAMEPAD_LEFT_TRIGGER] > XINPUT_GAMEPAD_MAX_CROSSTALK);
      case RETRO_DEVICE_ID_JOYPAD_R:
         return (g_xinput_states[port_num].xstate.Gamepad.bAnalogButtons[XINPUT_GAMEPAD_RIGHT_TRIGGER] > XINPUT_GAMEPAD_MAX_CROSSTALK);
      default:
         break;
   }
#else
   if (joykey < 10)
      return btn_word & button_index_to_bitmap_code[joykey];
#endif

   return false;
}