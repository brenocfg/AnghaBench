#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  action; } ;
typedef  TYPE_1__ menu_ctx_iterate_t ;
struct TYPE_5__ {int (* iterate ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_OK_DL_CONTENT_SETTINGS ; 
 int /*<<< orphan*/  MENU_SETTINGS ; 
 int /*<<< orphan*/  cpu_features_get_time_usec () ; 
 int /*<<< orphan*/  generic_action_ok_displaylist_push (char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_display_set_msg_force (int) ; 
 TYPE_3__* menu_driver_ctx ; 
 int /*<<< orphan*/  menu_driver_current_time_us ; 
 int /*<<< orphan*/  menu_driver_data ; 
 int menu_driver_pending_quick_menu ; 
 scalar_t__ menu_driver_selection_ptr ; 
 int /*<<< orphan*/  menu_entries_flush_stack (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_userdata ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool menu_driver_iterate(menu_ctx_iterate_t *iterate)
{
   /* Get current time */
   menu_driver_current_time_us = cpu_features_get_time_usec();

   if (menu_driver_pending_quick_menu)
   {
      /* If the user had requested that the Quick Menu
       * be spawned during the previous frame, do this now
       * and exit the function to go to the next frame.
       */

      menu_driver_pending_quick_menu = false;
      menu_entries_flush_stack(NULL, MENU_SETTINGS);
      menu_display_set_msg_force(true);

      generic_action_ok_displaylist_push("", NULL,
            "", 0, 0, 0, ACTION_OK_DL_CONTENT_SETTINGS);

      menu_driver_selection_ptr = 0;

      return true;
   }

   if (
         menu_driver_ctx          &&
         menu_driver_ctx->iterate &&
         menu_driver_ctx->iterate(menu_driver_data,
            menu_userdata, iterate->action) != -1)
      return true;

   return false;
}