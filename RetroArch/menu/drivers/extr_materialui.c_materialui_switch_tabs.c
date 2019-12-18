#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int (* action_content_list_switch ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ menu_file_list_cbs_t ;
struct TYPE_11__ {int /*<<< orphan*/  active; } ;
typedef  TYPE_3__ materialui_nav_bar_menu_tab_t ;
struct TYPE_9__ {int menu_navigation_wrapped; int num_menu_tabs; TYPE_3__* menu_tabs; scalar_t__ active_menu_tab_index; } ;
struct TYPE_12__ {int menu_stack_flushed; TYPE_1__ nav_bar; } ;
typedef  TYPE_4__ materialui_handle_t ;
typedef  int /*<<< orphan*/  file_list_t ;
typedef  enum menu_action { ____Placeholder_menu_action } menu_action ;

/* Variables and functions */
#define  MENU_ACTION_LEFT 129 
#define  MENU_ACTION_RIGHT 128 
 scalar_t__ file_list_get_actiondata_at_offset (int /*<<< orphan*/ *,size_t) ; 
 int materialui_preswitch_tabs (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/ * menu_entries_get_menu_stack_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * menu_entries_get_selection_buf_ptr (int /*<<< orphan*/ ) ; 
 size_t menu_navigation_get_selection () ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int materialui_switch_tabs(
      materialui_handle_t *mui, materialui_nav_bar_menu_tab_t *tab,
      enum menu_action action)
{
   materialui_nav_bar_menu_tab_t *target_tab = tab;

   /* Reset status parameters to default values
    * > Saves checks later */
   mui->nav_bar.menu_navigation_wrapped = false;
   mui->menu_stack_flushed              = false;

   /* If target tab is NULL, interpret menu action */
   if (!target_tab)
   {
      int target_tab_index = 0;

      switch (action)
      {
         case MENU_ACTION_LEFT:
            {
               target_tab_index = (int)mui->nav_bar.active_menu_tab_index - 1;

               if (target_tab_index < 0)
               {
                  target_tab_index = (int)mui->nav_bar.num_menu_tabs - 1;
                  mui->nav_bar.menu_navigation_wrapped = true;
               }
            }
            break;
         case MENU_ACTION_RIGHT:
            {
               target_tab_index = (int)mui->nav_bar.active_menu_tab_index + 1;

               if (target_tab_index >= mui->nav_bar.num_menu_tabs)
               {
                  target_tab_index = 0;
                  mui->nav_bar.menu_navigation_wrapped = true;
               }
            }
            break;
         default:
            /* Error condition */
            return -1;
      }

      target_tab = &mui->nav_bar.menu_tabs[target_tab_index];
   }

   /* Cannot switch to a tab that is already active */
   if (!target_tab->active)
   {
      file_list_t *selection_buf = menu_entries_get_selection_buf_ptr(0);
      file_list_t *menu_stack    = menu_entries_get_menu_stack_ptr(0);
      size_t selection           = menu_navigation_get_selection();
      menu_file_list_cbs_t *cbs  = selection_buf ?
            (menu_file_list_cbs_t*)file_list_get_actiondata_at_offset(
                  selection_buf, selection) : NULL;
      bool stack_flushed         = false;
      int ret                    = 0;

      /* Sanity check */
      if (!selection_buf || !menu_stack || !cbs)
         return -1;

      if (!cbs->action_content_list_switch)
         return -1;

      /* Perform pre-switch operations */
      stack_flushed = materialui_preswitch_tabs(mui, target_tab);

      /* Perform switch */
      ret = cbs->action_content_list_switch(
            selection_buf, menu_stack, "", "", 0);

      /* Note: If materialui_preswitch_tabs() flushes
       * the stack, then both materialui_preswitch_tabs()
       * AND action_content_list_switch() will cause the
       * menu to refresh
       * > For animation purposes, we therefore cannot
       *   register 'menu_stack_flushed' status until
       *   AFTER action_content_list_switch() has been
       *   called */
      mui->menu_stack_flushed = stack_flushed;

      return ret;
   }

   return 0;
}