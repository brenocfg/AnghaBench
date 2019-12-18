#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ menu_navigation_wraparound_enable; } ;
struct TYPE_8__ {TYPE_1__ bools; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_9__ {int size; scalar_t__ selection; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ menu_ctx_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_LIST_HORIZONTAL ; 
 int /*<<< orphan*/  MENU_LIST_PLAIN ; 
 int /*<<< orphan*/  MENU_LIST_TABS ; 
 int action_right_goto_tab () ; 
 int /*<<< orphan*/  action_right_scroll (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  menu_driver_list_get_selection (TYPE_3__*) ; 
 int /*<<< orphan*/  menu_driver_list_get_size (TYPE_3__*) ; 

__attribute__((used)) static int action_right_mainmenu(unsigned type, const char *label,
      bool wraparound)
{
   menu_ctx_list_t list_info;

   menu_driver_list_get_selection(&list_info);

   list_info.type = MENU_LIST_PLAIN;

   menu_driver_list_get_size(&list_info);

   if (list_info.size == 1)
   {
      menu_ctx_list_t list_horiz_info;
      menu_ctx_list_t list_tabs_info;
      settings_t      *settings = config_get_ptr();

      list_horiz_info.type      = MENU_LIST_HORIZONTAL;
      list_tabs_info.type       = MENU_LIST_TABS;

      menu_driver_list_get_size(&list_horiz_info);
      menu_driver_list_get_size(&list_tabs_info);

      if ((list_info.selection != (list_horiz_info.size + list_tabs_info.size))
         || settings->bools.menu_navigation_wraparound_enable)
         return action_right_goto_tab();
   }
   else
      action_right_scroll(0, "", false);

   return 0;
}