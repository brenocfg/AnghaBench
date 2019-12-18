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
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  materialui_navigation_set (void*,int) ; 

__attribute__((used)) static void materialui_list_set_selection(void *data, file_list_t *list)
{
   /* This is called upon MENU_ACTION_CANCEL
    * Have to set 'scroll' to false, otherwise
    * navigating backwards in the menu is absolutely
    * horrendous... */
   materialui_navigation_set(data, false);
}