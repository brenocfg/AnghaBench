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
 int /*<<< orphan*/  GTK_TREE_VIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_collapse_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree2_w ; 

void on_collapse_clicked(GtkButton * button, gpointer user_data)
{
	gtk_tree_view_collapse_all(GTK_TREE_VIEW(tree2_w));
}