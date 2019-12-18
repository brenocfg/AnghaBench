#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct retro_keybind {scalar_t__ joykey; scalar_t__ joyaxis; scalar_t__ key; } ;
struct TYPE_9__ {TYPE_2__* joypad; } ;
typedef  TYPE_3__ sdl_input_t ;
struct TYPE_10__ {float axis_threshold; int /*<<< orphan*/  joy_idx; TYPE_1__* auto_binds; } ;
typedef  TYPE_4__ rarch_joypad_info_t ;
typedef  int int16_t ;
typedef  enum input_device_type { ____Placeholder_input_device_type } input_device_type ;
struct TYPE_8__ {int /*<<< orphan*/  (* axis ) (int /*<<< orphan*/ ,scalar_t__ const) ;scalar_t__ (* button ) (int /*<<< orphan*/ ,scalar_t__) ;} ;
struct TYPE_7__ {scalar_t__ joykey; scalar_t__ joyaxis; } ;

/* Variables and functions */
 scalar_t__ AXIS_NONE ; 
 int INPUT_DEVICE_TYPE_JOYPAD ; 
 int INPUT_DEVICE_TYPE_KEYBOARD ; 
 scalar_t__ NO_BTN ; 
 scalar_t__ RETROK_LAST ; 
 scalar_t__ abs (int /*<<< orphan*/ ) ; 
 scalar_t__ sdl_key_pressed (scalar_t__) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__ const) ; 

__attribute__((used)) static int16_t sdl_joypad_device_state(sdl_input_t *sdl,
      rarch_joypad_info_t joypad_info,
      const struct retro_keybind *binds,
      unsigned port, unsigned id, enum input_device_type *device)
{
   /* Auto-binds are per joypad, not per user. */
   const uint64_t joykey  = (binds[id].joykey != NO_BTN)
      ? binds[id].joykey : joypad_info.auto_binds[id].joykey;
   const uint32_t joyaxis = (binds[id].joyaxis != AXIS_NONE)
      ? binds[id].joyaxis : joypad_info.auto_binds[id].joyaxis;

   if ((binds[id].key < RETROK_LAST) && sdl_key_pressed(binds[id].key))
   {
      *device = INPUT_DEVICE_TYPE_KEYBOARD;
      return 1;
   }

   if ((uint16_t)joykey != NO_BTN && sdl->joypad->button(joypad_info.joy_idx, (uint16_t)joykey))
   {
      *device = INPUT_DEVICE_TYPE_JOYPAD;
      return 1;
   }

   if (((float)abs(sdl->joypad->axis(joypad_info.joy_idx, joyaxis)) / 0x8000) > joypad_info.axis_threshold)
   {
      *device = INPUT_DEVICE_TYPE_JOYPAD;
      return 1;
   }

   return 0;
}