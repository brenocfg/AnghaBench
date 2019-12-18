#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  label; int /*<<< orphan*/  enum_idx; int /*<<< orphan*/  list; } ;
typedef  TYPE_1__ menu_displaylist_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLIST_HELP ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_HELP ; 
 int /*<<< orphan*/  menu_dialog_is_push_pending () ; 
 int /*<<< orphan*/  menu_displaylist_ctl (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  menu_displaylist_info_init (TYPE_1__*) ; 
 int /*<<< orphan*/  menu_entries_get_menu_stack_ptr (int /*<<< orphan*/ ) ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

void menu_dialog_push(void)
{
   menu_displaylist_info_t info;
   const char *label;

   if (!menu_dialog_is_push_pending())
      return;

   menu_displaylist_info_init(&info);

   info.list                 = menu_entries_get_menu_stack_ptr(0);
   info.enum_idx             = MENU_ENUM_LABEL_HELP;

   /* Set the label string, if it exists. */
   label                     = msg_hash_to_str(MENU_ENUM_LABEL_HELP);
   if (label)
      info.label             = strdup(label);

   menu_displaylist_ctl(DISPLAYLIST_HELP, &info);
}