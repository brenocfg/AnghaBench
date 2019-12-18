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
struct TYPE_8__ {scalar_t__ menu_navigation_wraparound_enable; } ;
struct TYPE_11__ {TYPE_1__ bools; } ;
typedef  TYPE_4__ settings_t ;
struct TYPE_9__ {double* integer; } ;
struct TYPE_10__ {TYPE_2__ target; } ;
struct TYPE_12__ {double min; double step; double max; TYPE_3__ value; scalar_t__ enforce_minrange; } ;
typedef  TYPE_5__ rarch_setting_t ;

/* Variables and functions */
 TYPE_4__* config_get_ptr () ; 

__attribute__((used)) static int setting_int_action_left_default(rarch_setting_t *setting, bool wraparound)
{
   double               min = 0.0f;

   if (!setting)
      return -1;

   min = setting->min;

   (void)wraparound; /* TODO/FIXME - handle this */

   *setting->value.target.integer = *setting->value.target.integer - setting->step;

   if (setting->enforce_minrange)
   {
      if (*setting->value.target.integer < min)
      {
         settings_t *settings = config_get_ptr();
         double           max = setting->max;

         if (settings && settings->bools.menu_navigation_wraparound_enable)
            *setting->value.target.integer = max;
         else
            *setting->value.target.integer = min;
      }
   }

   return 0;
}