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
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  GtkButton ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FULL_VIEW ; 
 int /*<<< orphan*/  GTK_PANED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  back_btn ; 
 int /*<<< orphan*/  display_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_paned_set_position (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_store_clear (scalar_t__) ; 
 int /*<<< orphan*/  gtk_widget_hide (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpaned ; 
 int /*<<< orphan*/  rootmenu ; 
 int /*<<< orphan*/  tree1_w ; 
 scalar_t__ tree2 ; 
 int /*<<< orphan*/  view_mode ; 

void on_full_clicked(GtkButton * button, gpointer user_data)
{
	view_mode = FULL_VIEW;
	gtk_paned_set_position(GTK_PANED(hpaned), 0);
	gtk_widget_hide(tree1_w);
	if (tree2)
		gtk_tree_store_clear(tree2);
	display_tree(&rootmenu);
	gtk_widget_set_sensitive(back_btn, FALSE);
}