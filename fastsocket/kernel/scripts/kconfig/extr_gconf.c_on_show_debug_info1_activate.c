#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gpointer ;
struct TYPE_2__ {int /*<<< orphan*/  active; } ;
typedef  int /*<<< orphan*/  GtkMenuItem ;

/* Variables and functions */
 TYPE_1__* GTK_CHECK_MENU_ITEM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rootmenu ; 
 int /*<<< orphan*/  show_debug ; 
 int /*<<< orphan*/  update_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
on_show_debug_info1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	show_debug = GTK_CHECK_MENU_ITEM(menuitem)->active;
	update_tree(&rootmenu, NULL);
}