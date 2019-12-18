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
struct TYPE_7__ {float step; } ;
typedef  TYPE_2__ rarch_setting_t ;
struct TYPE_6__ {scalar_t__ action_press_time; } ;
struct TYPE_8__ {TYPE_1__ menu; } ;
typedef  TYPE_3__ global_t ;

/* Variables and functions */
 scalar_t__ _12_SECONDS ; 
 scalar_t__ _15_SECONDS ; 
 scalar_t__ _18_SECONDS ; 
 scalar_t__ _21_SECONDS ; 
 scalar_t__ _3_SECONDS ; 
 scalar_t__ _6_SECONDS ; 
 scalar_t__ _9_SECONDS ; 
 TYPE_3__* global_get_ptr () ; 

__attribute__((used)) static float recalc_step_based_on_length_of_action(rarch_setting_t *setting)
{
   float       step = setting->step;
   global_t *global = global_get_ptr();

   if ( global )
   {
      if ( global->menu.action_press_time  > _21_SECONDS)
         step = setting->step*1000000.0f;
      else if ( global->menu.action_press_time  > _18_SECONDS)
         step = setting->step*100000.0f;
      else if ( global->menu.action_press_time  > _15_SECONDS)
         step = setting->step*10000.0f;
      else if ( global->menu.action_press_time  > _12_SECONDS)
         step = setting->step*1000.0f;
      else if ( global->menu.action_press_time  > _9_SECONDS)
         step = setting->step*100.0f;
      else if ( global->menu.action_press_time  > _6_SECONDS)
         step = setting->step*10.0f;
      else if ( global->menu.action_press_time  > _3_SECONDS)
         step = setting->step*5.0f;
      else
         step = setting->step;
   }
   return step < setting->step ? setting->step : step;
}