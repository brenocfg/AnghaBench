#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int (* action_up ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* action_down ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* action_cancel ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ;int (* action_ok ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ;int (* action_start ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* action_left ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int (* action_right ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int (* action_info ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* action_select ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ;int (* action_scan ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ;int /*<<< orphan*/  (* action_refresh ) (TYPE_4__*,TYPE_4__*) ;} ;
typedef  TYPE_2__ menu_file_list_cbs_t ;
struct TYPE_12__ {int /*<<< orphan*/  type; int /*<<< orphan*/  label; int /*<<< orphan*/  path; int /*<<< orphan*/  entry_idx; } ;
typedef  TYPE_3__ menu_entry_t ;
struct TYPE_13__ {TYPE_1__* list; } ;
typedef  TYPE_4__ file_list_t ;
typedef  enum menu_action { ____Placeholder_menu_action } menu_action ;
struct TYPE_10__ {scalar_t__ actiondata; } ;

/* Variables and functions */
#define  MENU_ACTION_CANCEL 140 
#define  MENU_ACTION_DOWN 139 
#define  MENU_ACTION_INFO 138 
#define  MENU_ACTION_LEFT 137 
#define  MENU_ACTION_OK 136 
#define  MENU_ACTION_RIGHT 135 
#define  MENU_ACTION_SCAN 134 
#define  MENU_ACTION_SCROLL_DOWN 133 
#define  MENU_ACTION_SCROLL_UP 132 
#define  MENU_ACTION_SEARCH 131 
#define  MENU_ACTION_SELECT 130 
#define  MENU_ACTION_START 129 
#define  MENU_ACTION_UP 128 
 int /*<<< orphan*/  MENU_ENTRIES_CTL_NEEDS_REFRESH ; 
 int /*<<< orphan*/  MENU_ENTRIES_CTL_UNSET_REFRESH ; 
 int /*<<< orphan*/  MENU_NAVIGATION_CTL_ASCEND_ALPHABET ; 
 int /*<<< orphan*/  MENU_NAVIGATION_CTL_DESCEND_ALPHABET ; 
 int /*<<< orphan*/  menu_driver_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ menu_entries_ctl (int /*<<< orphan*/ ,int*) ; 
 TYPE_4__* menu_entries_get_menu_stack_ptr (int /*<<< orphan*/ ) ; 
 TYPE_4__* menu_entries_get_selection_buf_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_input_dialog_start_search () ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  stub11 (TYPE_4__*,TYPE_4__*) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub9 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

int generic_menu_entry_action(
      void *userdata, menu_entry_t *entry, size_t i, enum menu_action action)
{
   int ret                    = 0;
   file_list_t *selection_buf = menu_entries_get_selection_buf_ptr(0);
   menu_file_list_cbs_t *cbs  = selection_buf ?
      (menu_file_list_cbs_t*)selection_buf->list[i].actiondata : NULL;

   switch (action)
   {
      case MENU_ACTION_UP:
         if (cbs && cbs->action_up)
            ret = cbs->action_up(entry->type, entry->label);
         break;
      case MENU_ACTION_DOWN:
         if (cbs && cbs->action_down)
            ret = cbs->action_down(entry->type, entry->label);
         break;
      case MENU_ACTION_SCROLL_UP:
         menu_driver_ctl(MENU_NAVIGATION_CTL_DESCEND_ALPHABET, NULL);
         break;
      case MENU_ACTION_SCROLL_DOWN:
         menu_driver_ctl(MENU_NAVIGATION_CTL_ASCEND_ALPHABET, NULL);
         break;
      case MENU_ACTION_CANCEL:
         if (cbs && cbs->action_cancel)
            ret = cbs->action_cancel(entry->path,
                  entry->label, entry->type, i);
         break;
      case MENU_ACTION_OK:
         if (cbs && cbs->action_ok)
            ret = cbs->action_ok(entry->path,
                  entry->label, entry->type, i, entry->entry_idx);
         break;
      case MENU_ACTION_START:
         if (cbs && cbs->action_start)
            ret = cbs->action_start(entry->type, entry->label);
         break;
      case MENU_ACTION_LEFT:
         if (cbs && cbs->action_left)
            ret = cbs->action_left(entry->type, entry->label, false);
         break;
      case MENU_ACTION_RIGHT:
         if (cbs && cbs->action_right)
            ret = cbs->action_right(entry->type, entry->label, false);
         break;
      case MENU_ACTION_INFO:
         if (cbs && cbs->action_info)
            ret = cbs->action_info(entry->type, entry->label);
         break;
      case MENU_ACTION_SELECT:
         if (cbs && cbs->action_select)
            ret = cbs->action_select(entry->path,
                  entry->label, entry->type, i);
         break;
      case MENU_ACTION_SEARCH:
         menu_input_dialog_start_search();
         break;
      case MENU_ACTION_SCAN:
         if (cbs && cbs->action_scan)
            ret = cbs->action_scan(entry->path,
                  entry->label, entry->type, i);
         break;
      default:
         break;
   }

   cbs = selection_buf ? (menu_file_list_cbs_t*)
      selection_buf->list[i].actiondata : NULL;

   if (cbs && cbs->action_refresh)
   {
      if (menu_entries_ctl(MENU_ENTRIES_CTL_NEEDS_REFRESH, NULL))
      {
         bool refresh            = false;
         file_list_t *menu_stack = menu_entries_get_menu_stack_ptr(0);

         cbs->action_refresh(selection_buf, menu_stack);
         menu_entries_ctl(MENU_ENTRIES_CTL_UNSET_REFRESH, &refresh);
      }
   }

   return ret;
}