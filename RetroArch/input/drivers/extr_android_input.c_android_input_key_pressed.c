#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_9__ {float axis_threshold; scalar_t__ joy_idx; TYPE_5__* auto_binds; } ;
typedef  TYPE_2__ rarch_joypad_info_t ;
struct TYPE_10__ {TYPE_1__* joypad; } ;
typedef  TYPE_3__ android_input_t ;
struct TYPE_12__ {scalar_t__ joykey; scalar_t__ joyaxis; } ;
struct TYPE_11__ {scalar_t__ joykey; scalar_t__ joyaxis; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* axis ) (scalar_t__,scalar_t__) ;scalar_t__ (* button ) (scalar_t__,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ AXIS_NONE ; 
 int /*<<< orphan*/  INPUT_ACTION_AXIS_THRESHOLD ; 
 scalar_t__ NO_BTN ; 
 int RARCH_BIND_LIST_END ; 
 scalar_t__ abs (int /*<<< orphan*/ ) ; 
 scalar_t__ android_keyboard_port_input_pressed (TYPE_4__*,int) ; 
 TYPE_5__** input_autoconf_binds ; 
 TYPE_4__** input_config_binds ; 
 float* input_driver_get_float (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool android_input_key_pressed(android_input_t *android, int key)
{
   uint64_t joykey;
   uint32_t joyaxis;
   rarch_joypad_info_t joypad_info;
   joypad_info.joy_idx        = 0;
   joypad_info.auto_binds     = input_autoconf_binds[0];
   joypad_info.axis_threshold = *
      (input_driver_get_float(INPUT_ACTION_AXIS_THRESHOLD));

   if((key < RARCH_BIND_LIST_END)
         && android_keyboard_port_input_pressed(input_config_binds[0],
            key))
      return true;

   joykey                     = 
      (input_config_binds[0][key].joykey != NO_BTN)
      ? input_config_binds[0][key].joykey 
      : joypad_info.auto_binds[key].joykey;
   joyaxis                    = 
      (input_config_binds[0][key].joyaxis != AXIS_NONE)
      ? input_config_binds[0][key].joyaxis 
      : joypad_info.auto_binds[key].joyaxis;

   if ((uint16_t)joykey != NO_BTN && android->joypad->button(joypad_info.joy_idx, (uint16_t)joykey))
      return true;
   if (((float)abs(android->joypad->axis(joypad_info.joy_idx, joyaxis)) / 0x8000) > joypad_info.axis_threshold)
      return true;
   return false;
}