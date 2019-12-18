#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* joypad; } ;
typedef  TYPE_3__ uwp_input_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct retro_keybind {scalar_t__ key; scalar_t__ joykey; scalar_t__ joyaxis; int /*<<< orphan*/  mbutton; scalar_t__ valid; } ;
struct TYPE_11__ {float axis_threshold; int /*<<< orphan*/  joy_idx; TYPE_1__* auto_binds; } ;
typedef  TYPE_4__ rarch_joypad_info_t ;
struct TYPE_12__ {int /*<<< orphan*/  keyboard_mapping_blocked; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* axis ) (int /*<<< orphan*/ ,scalar_t__ const) ;scalar_t__ (* button ) (int /*<<< orphan*/ ,scalar_t__) ;} ;
struct TYPE_8__ {scalar_t__ joykey; scalar_t__ joyaxis; } ;

/* Variables and functions */
 scalar_t__ AXIS_NONE ; 
 scalar_t__ NO_BTN ; 
 unsigned int RARCH_GAME_FOCUS_TOGGLE ; 
 scalar_t__ RETROK_LAST ; 
 scalar_t__ abs (int /*<<< orphan*/ ) ; 
 TYPE_7__ input_uwp ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__ const) ; 
 scalar_t__ uwp_keyboard_pressed (scalar_t__) ; 
 scalar_t__ uwp_mouse_state (unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool uwp_pressed_joypad(uwp_input_t *uwp,
   rarch_joypad_info_t joypad_info,
   const struct retro_keybind *binds,
   unsigned port, unsigned id)
{
   const struct retro_keybind *bind = &binds[id];

   /* First, process the keyboard bindings */
   if ((bind->key < RETROK_LAST) && uwp_keyboard_pressed(bind->key))
      if ((id == RARCH_GAME_FOCUS_TOGGLE) || !input_uwp.keyboard_mapping_blocked)
         return true;

   /* Then, process the joypad bindings */
   if (binds && binds[id].valid)
   {
      /* Auto-binds are per joypad, not per user. */
      const uint64_t joykey  = (binds[id].joykey != NO_BTN)
         ? binds[id].joykey : joypad_info.auto_binds[id].joykey;
      const uint32_t joyaxis = (binds[id].joyaxis != AXIS_NONE)
         ? binds[id].joyaxis : joypad_info.auto_binds[id].joyaxis;

      if (uwp_mouse_state(port, bind->mbutton, false))
         return true;
      if ((uint16_t)joykey != NO_BTN && uwp->joypad->button(joypad_info.joy_idx, (uint16_t)joykey))
         return true;
      if (((float)abs(uwp->joypad->axis(joypad_info.joy_idx, joyaxis)) / 0x8000) > joypad_info.axis_threshold)
         return true;
   }

   return false;
}