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
typedef  scalar_t__ int16_t ;
struct TYPE_5__ {size_t latest_idx; TYPE_3__* entries; } ;
struct TYPE_6__ {TYPE_1__ main; } ;
typedef  TYPE_2__ hid_controller_t ;
struct TYPE_7__ {int button_state; scalar_t__ left_stick_x; scalar_t__ left_stick_y; scalar_t__ right_stick_x; scalar_t__ right_stick_y; } ;
typedef  TYPE_3__ hid_controller_state_entry_t ;
struct TYPE_8__ {TYPE_2__* controllers; } ;

/* Variables and functions */
 size_t RETRO_DEVICE_ID_ANALOG_X ; 
 size_t RETRO_DEVICE_ID_ANALOG_Y ; 
 size_t RETRO_DEVICE_INDEX_ANALOG_LEFT ; 
 size_t RETRO_DEVICE_INDEX_ANALOG_RIGHT ; 
 scalar_t__*** analog_state ; 
 TYPE_4__* hid_get_shared_memory () ; 
 int* pad_state ; 

__attribute__((used)) static void switch_joypad_poll(void)
{
   int16_t lsx, lsy, rsx, rsy;
   hid_controller_t    *controllers  = hid_get_shared_memory()->controllers;
   hid_controller_t           *cont  = &controllers[0];
   hid_controller_state_entry_t ent  = cont->main.entries[cont->main.latest_idx];
   hid_controller_state_entry_t ent8 = (cont+8)->main.entries[(cont+8)->main.latest_idx];
   pad_state[0]                      = ent.button_state | ent8.button_state;

   lsx                               = ent.left_stick_x;
   lsy                               = ent.left_stick_y;
   rsx                               = ent.right_stick_x;
   rsy                               = ent.right_stick_y;

   if (ent8.left_stick_x != 0 || ent8.left_stick_y != 0)
   {
      /* handheld overrides player 1 */
	   lsx                            = ent8.left_stick_x;
	   lsy                            = ent8.left_stick_y;
   }

   if (ent8.right_stick_x != 0 || ent8.right_stick_y != 0)
   {
      /* handheld overrides player 1 */
	   rsx                            = ent8.right_stick_x;
	   rsy                            = ent8.right_stick_y;
   }

   analog_state[0][RETRO_DEVICE_INDEX_ANALOG_LEFT]
      [RETRO_DEVICE_ID_ANALOG_X]     = lsx;
   analog_state[0][RETRO_DEVICE_INDEX_ANALOG_LEFT]
      [RETRO_DEVICE_ID_ANALOG_Y]     = -lsy;
   analog_state[0][RETRO_DEVICE_INDEX_ANALOG_RIGHT]
      [RETRO_DEVICE_ID_ANALOG_X]     = rsx;
   analog_state[0][RETRO_DEVICE_INDEX_ANALOG_RIGHT]
      [RETRO_DEVICE_ID_ANALOG_Y]     = -rsy;
}