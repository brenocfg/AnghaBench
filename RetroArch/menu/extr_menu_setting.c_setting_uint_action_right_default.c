#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ menu_navigation_wraparound_enable; } ;
struct TYPE_12__ {TYPE_1__ bools; } ;
typedef  TYPE_4__ settings_t ;
struct TYPE_10__ {float* unsigned_integer; } ;
struct TYPE_11__ {TYPE_2__ target; } ;
struct TYPE_13__ {double max; double min; TYPE_3__ value; scalar_t__ enforce_maxrange; } ;
typedef  TYPE_5__ rarch_setting_t ;

/* Variables and functions */
 TYPE_4__* config_get_ptr () ; 
 float recalc_step_based_on_length_of_action (TYPE_5__*) ; 

int setting_uint_action_right_default(
      rarch_setting_t *setting, bool wraparound)
{
   double               max  = 0.0f;
   float                step = 0.0f;

   if (!setting)
      return -1;

   max                       = setting->max;
   step                      = 
      recalc_step_based_on_length_of_action(setting);

   *setting->value.target.unsigned_integer =
      *setting->value.target.unsigned_integer + step;

   if (setting->enforce_maxrange)
   {
      if (*setting->value.target.unsigned_integer > max)
      {
         settings_t *settings = config_get_ptr();

         double           min = setting->min;

         if (settings && settings->bools.menu_navigation_wraparound_enable)
            *setting->value.target.unsigned_integer = min;
         else
            *setting->value.target.unsigned_integer = max;
      }
   }

   return 0;
}