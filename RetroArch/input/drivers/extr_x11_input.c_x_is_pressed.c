#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* joypad; } ;
typedef  TYPE_3__ x11_input_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct retro_keybind {scalar_t__ key; scalar_t__ joykey; scalar_t__ joyaxis; int /*<<< orphan*/  mbutton; scalar_t__ valid; } ;
struct TYPE_13__ {float axis_threshold; int /*<<< orphan*/  joy_idx; TYPE_1__* auto_binds; } ;
typedef  TYPE_4__ rarch_joypad_info_t ;
struct TYPE_14__ {int /*<<< orphan*/  keyboard_mapping_blocked; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* axis ) (int /*<<< orphan*/ ,scalar_t__ const) ;scalar_t__ (* button ) (int /*<<< orphan*/ ,scalar_t__) ;} ;
struct TYPE_10__ {scalar_t__ joykey; scalar_t__ joyaxis; } ;

/* Variables and functions */
 scalar_t__ AXIS_NONE ; 
 scalar_t__ NO_BTN ; 
 unsigned int RARCH_GAME_FOCUS_TOGGLE ; 
 scalar_t__ RETROK_LAST ; 
 scalar_t__ abs (int /*<<< orphan*/ ) ; 
 TYPE_9__ input_x ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__ const) ; 
 scalar_t__ x_keyboard_pressed (TYPE_3__*,scalar_t__) ; 
 scalar_t__ x_mouse_button_pressed (TYPE_3__*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool x_is_pressed(x11_input_t *x11,
      rarch_joypad_info_t joypad_info,
      const struct retro_keybind *binds,
      unsigned port, unsigned id)
{
   const struct retro_keybind *bind = &binds[id];

   if ((bind->key < RETROK_LAST) && x_keyboard_pressed(x11, bind->key) )
      if ((id == RARCH_GAME_FOCUS_TOGGLE) || !input_x.keyboard_mapping_blocked)
         return true;

   if (binds && binds[id].valid)
   {
      /* Auto-binds are per joypad, not per user. */
      const uint64_t joykey  = (binds[id].joykey != NO_BTN)
         ? binds[id].joykey : joypad_info.auto_binds[id].joykey;
      const uint32_t joyaxis = (binds[id].joyaxis != AXIS_NONE)
         ? binds[id].joyaxis : joypad_info.auto_binds[id].joyaxis;

      if (x_mouse_button_pressed(x11, port, bind->mbutton))
         return true;
      if ((uint16_t)joykey != NO_BTN 
            && x11->joypad->button(joypad_info.joy_idx, (uint16_t)joykey))
         return true;
      if (((float)abs(x11->joypad->axis(joypad_info.joy_idx, joyaxis)) / 0x8000) > joypad_info.axis_threshold)
         return true;
   }

   return false;
}