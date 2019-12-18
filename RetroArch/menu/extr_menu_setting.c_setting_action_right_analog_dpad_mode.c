#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* input_analog_dpad_mode; } ;
struct TYPE_7__ {int modified; TYPE_1__ uints; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_8__ {unsigned int index_offset; } ;
typedef  TYPE_3__ rarch_setting_t ;

/* Variables and functions */
 int ANALOG_DPAD_LAST ; 
 TYPE_2__* config_get_ptr () ; 

__attribute__((used)) static int setting_action_right_analog_dpad_mode(rarch_setting_t *setting, bool wraparound)
{
   unsigned port = 0;
   settings_t      *settings = config_get_ptr();

   if (!setting)
      return -1;

   port = setting->index_offset;

   settings->modified                     = true;
   settings->uints.input_analog_dpad_mode[port] =
      (settings->uints.input_analog_dpad_mode[port] + 1)
      % ANALOG_DPAD_LAST;

   return 0;
}