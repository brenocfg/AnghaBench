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
typedef  int /*<<< orphan*/  menu_file_list_cbs_t ;
typedef  int /*<<< orphan*/  menu_entry_t ;
struct TYPE_8__ {int type; int /*<<< orphan*/  enabled; } ;
typedef  TYPE_2__ materialui_nav_bar_action_tab_t ;
struct TYPE_7__ {unsigned int num_menu_tabs; scalar_t__ location; int /*<<< orphan*/ * menu_tabs; TYPE_2__ resume_tab; TYPE_2__ back_tab; } ;
struct TYPE_9__ {TYPE_1__ nav_bar; } ;
typedef  TYPE_3__ materialui_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_MENU_TOGGLE ; 
 int /*<<< orphan*/  MENU_ACTION_CANCEL ; 
 int /*<<< orphan*/  MENU_ACTION_NOOP ; 
#define  MUI_NAV_BAR_ACTION_TAB_BACK 129 
#define  MUI_NAV_BAR_ACTION_TAB_RESUME 128 
 scalar_t__ MUI_NAV_BAR_LOCATION_RIGHT ; 
 unsigned int MUI_NAV_BAR_NUM_ACTION_TABS ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int materialui_menu_entry_action (TYPE_3__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int materialui_switch_tabs (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int materialui_pointer_up_nav_bar(
      materialui_handle_t *mui,
      unsigned x, unsigned y, unsigned width, unsigned height, size_t selection,
      menu_file_list_cbs_t *cbs, menu_entry_t *entry, unsigned action)
{
   unsigned num_tabs = mui->nav_bar.num_menu_tabs + MUI_NAV_BAR_NUM_ACTION_TABS;
   unsigned tab_index;

   /* Determine tab 'index' - integer corresponding
    * to physical location on screen */
   if (mui->nav_bar.location == MUI_NAV_BAR_LOCATION_RIGHT)
      tab_index = y / (height / num_tabs);
   else
      tab_index = x / (width / num_tabs);

   /* Check if this is an action tab */
   if ((tab_index == 0) || (tab_index >= num_tabs - 1))
   {
      materialui_nav_bar_action_tab_t *target_tab = NULL;

      if (mui->nav_bar.location == MUI_NAV_BAR_LOCATION_RIGHT)
         target_tab = (tab_index == 0) ?
               &mui->nav_bar.resume_tab : &mui->nav_bar.back_tab;
      else
         target_tab = (tab_index == 0) ?
               &mui->nav_bar.back_tab : &mui->nav_bar.resume_tab;

      switch (target_tab->type)
      {
         case MUI_NAV_BAR_ACTION_TAB_BACK:
            if (target_tab->enabled)
               return materialui_menu_entry_action(mui, entry, selection, MENU_ACTION_CANCEL);
            break;
         case MUI_NAV_BAR_ACTION_TAB_RESUME:
            if (target_tab->enabled)
               return command_event(CMD_EVENT_MENU_TOGGLE, NULL) ? 0 : -1;
            break;
         default:
            break;
      }
   }
   /* Tab is a menu tab */
   else
      return materialui_switch_tabs(
            mui, &mui->nav_bar.menu_tabs[tab_index - 1], MENU_ACTION_NOOP);

   return 0;
}