#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  menu_displaylist_info_t ;
typedef  enum menu_displaylist_ctl_state { ____Placeholder_menu_displaylist_ctl_state } menu_displaylist_ctl_state ;

/* Variables and functions */
 int menu_cbs_exit () ; 
 int /*<<< orphan*/  menu_displaylist_ctl (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_displaylist_process (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int deferred_push_dlist(menu_displaylist_info_t *info, enum menu_displaylist_ctl_state state)
{
   if (!menu_displaylist_ctl(state, info))
      return menu_cbs_exit();
   menu_displaylist_process(info);
   return 0;
}