#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_8__ {int (* button ) (unsigned int,int) ;} ;
struct TYPE_5__ {int wButtons; } ;
struct TYPE_6__ {TYPE_1__ Gamepad; } ;
struct TYPE_7__ {TYPE_2__ xstate; int /*<<< orphan*/  connected; } ;

/* Variables and functions */
 unsigned int GET_HAT_DIR (int) ; 
#define  HAT_DOWN_MASK 131 
#define  HAT_LEFT_MASK 130 
#define  HAT_RIGHT_MASK 129 
#define  HAT_UP_MASK 128 
 int XINPUT_GAMEPAD_DPAD_DOWN ; 
 int XINPUT_GAMEPAD_DPAD_LEFT ; 
 int XINPUT_GAMEPAD_DPAD_RIGHT ; 
 int XINPUT_GAMEPAD_DPAD_UP ; 
 int* button_index_to_bitmap_code ; 
 TYPE_4__ dinput_joypad ; 
 int g_xinput_num_buttons ; 
 TYPE_3__* g_xinput_states ; 
 int pad_index_to_xuser_index (unsigned int) ; 
 int stub1 (unsigned int,int) ; 

__attribute__((used)) static bool xinput_joypad_button(unsigned port_num, uint16_t joykey)
{
   uint16_t btn_word    = 0;
   unsigned hat_dir     = 0;
   int xuser            = pad_index_to_xuser_index(port_num);

#ifdef HAVE_DINPUT
   if (xuser == -1)
      return dinput_joypad.button(port_num, joykey);
#endif

   if (!(g_xinput_states[xuser].connected))
      return false;

   btn_word = g_xinput_states[xuser].xstate.Gamepad.wButtons;
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

   if (joykey < g_xinput_num_buttons)
      return btn_word & button_index_to_bitmap_code[joykey];

   return false;
}