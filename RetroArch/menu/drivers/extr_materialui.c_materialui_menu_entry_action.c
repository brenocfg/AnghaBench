#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int path_enabled; int label_enabled; int rich_label_enabled; int value_enabled; int sublabel_enabled; } ;
typedef  TYPE_1__ menu_entry_t ;
typedef  int /*<<< orphan*/  materialui_handle_t ;
typedef  enum menu_action { ____Placeholder_menu_action } menu_action ;

/* Variables and functions */
 int generic_menu_entry_action (void*,TYPE_1__*,size_t,int) ; 
 int materialui_parse_menu_entry_action (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  menu_entry_get (TYPE_1__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  menu_entry_init (TYPE_1__*) ; 
 size_t menu_navigation_get_selection () ; 

__attribute__((used)) static int materialui_menu_entry_action(
      void *userdata, menu_entry_t *entry,
      size_t i, enum menu_action action)
{
   materialui_handle_t *mui = (materialui_handle_t*)userdata;
   menu_entry_t *entry_ptr  = entry;
   size_t selection         = i;
   size_t new_selection;
   enum menu_action new_action;

   if (!mui)
      generic_menu_entry_action(userdata, entry, i, action);

   /* Process input action */
   new_action = materialui_parse_menu_entry_action(mui, action);

   /* NOTE: It would make sense to stop here if the
    * resultant action is a NOOP (MENU_ACTION_NOOP),
    * but the underlying menu code requires us to call
    * generic_menu_entry_action() even in this case.
    * If we don't, internal breakage will occur - so
    * ignore new_action type, and just continue
    * regardless... */

   /* Check whether current selection has changed
    * (due to automatic on screen entry selection...) */
   new_selection = menu_navigation_get_selection();

   if (new_selection != selection)
   {
      static menu_entry_t new_entry;

      /* Selection has changed - must update entry
       * pointer (we could probably get away without
       * doing this, but it would break the API...) */
      menu_entry_init(&new_entry);
      new_entry.path_enabled       = false;
      new_entry.label_enabled      = false;
      new_entry.rich_label_enabled = false;
      new_entry.value_enabled      = false;
      new_entry.sublabel_enabled   = false;
      menu_entry_get(&new_entry, 0, new_selection, NULL, true);
      entry_ptr                    = &new_entry;
   }

   /* Call standard generic_menu_entry_action() function */
   return generic_menu_entry_action(userdata, entry_ptr, new_selection, new_action);
}