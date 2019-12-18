#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int battery_enabled; int charging; unsigned int percent; int /*<<< orphan*/  len; int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ menu_display_ctx_powerstate_t ;
typedef  enum frontend_powerstate { ____Placeholder_frontend_powerstate } frontend_powerstate ;

/* Variables and functions */
 int FRONTEND_POWERSTATE_CHARGING ; 
 int FRONTEND_POWERSTATE_NONE ; 
 int FRONTEND_POWERSTATE_NO_SOURCE ; 
 scalar_t__ POWERSTATE_CHECK_INTERVAL ; 
 int get_last_powerstate (int*) ; 
 scalar_t__ menu_driver_current_time_us ; 
 scalar_t__ menu_driver_powerstate_last_time_us ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  task_push_get_powerstate () ; 

void menu_display_powerstate(menu_display_ctx_powerstate_t *powerstate)
{
   int percent                    = 0;
   enum frontend_powerstate state = FRONTEND_POWERSTATE_NONE;

   if (!powerstate)
      return;

   /* Trigger an update, if required */
   if (menu_driver_current_time_us - menu_driver_powerstate_last_time_us >=
         POWERSTATE_CHECK_INTERVAL)
   {
      menu_driver_powerstate_last_time_us = menu_driver_current_time_us;
      task_push_get_powerstate();
   }

   /* Get last recorded state */
   state = get_last_powerstate(&percent);

   /* Populate menu_display_ctx_powerstate_t */
   powerstate->battery_enabled = (state != FRONTEND_POWERSTATE_NONE) &&
                                 (state != FRONTEND_POWERSTATE_NO_SOURCE);

   if (powerstate->battery_enabled)
   {
      powerstate->charging = (state == FRONTEND_POWERSTATE_CHARGING);
      powerstate->percent  = percent > 0 ? (unsigned)percent : 0;
      snprintf(powerstate->s, powerstate->len, "%u%%", powerstate->percent);
   }
   else
   {
      powerstate->charging = false;
      powerstate->percent  = 0;
   }
}