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
typedef  scalar_t__ gint ;
typedef  int /*<<< orphan*/  GtkTreeViewColumn ;

/* Variables and functions */
 scalar_t__ COL_NUMBER ; 
 int /*<<< orphan*/  GTK_TREE_VIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_column (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tree2_w ; 

__attribute__((used)) static gint column2index(GtkTreeViewColumn * column)
{
	gint i;

	for (i = 0; i < COL_NUMBER; i++) {
		GtkTreeViewColumn *col;

		col = gtk_tree_view_get_column(GTK_TREE_VIEW(tree2_w), i);
		if (col == column)
			return i;
	}

	return -1;
}