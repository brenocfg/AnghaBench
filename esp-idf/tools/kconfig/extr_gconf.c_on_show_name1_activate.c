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
typedef  int /*<<< orphan*/  GtkTreeViewColumn ;
typedef  int /*<<< orphan*/  GtkMenuItem ;

/* Variables and functions */
 int /*<<< orphan*/  COL_NAME ; 
 TYPE_1__* GTK_CHECK_MENU_ITEM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TREE_VIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_column_set_visible (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_column (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_name ; 
 int /*<<< orphan*/  tree2_w ; 

void on_show_name1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	GtkTreeViewColumn *col;

	show_name = GTK_CHECK_MENU_ITEM(menuitem)->active;
	col = gtk_tree_view_get_column(GTK_TREE_VIEW(tree2_w), COL_NAME);
	if (col)
		gtk_tree_view_column_set_visible(col, show_name);
}