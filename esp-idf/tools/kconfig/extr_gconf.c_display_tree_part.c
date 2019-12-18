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

/* Variables and functions */
 int /*<<< orphan*/  GTK_TREE_VIEW (int /*<<< orphan*/ ) ; 
 scalar_t__ SINGLE_VIEW ; 
 scalar_t__ SPLIT_VIEW ; 
 int /*<<< orphan*/  browsed ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  display_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_store_clear (scalar_t__) ; 
 int /*<<< orphan*/  gtk_tree_view_expand_all (int /*<<< orphan*/ ) ; 
 scalar_t__ tree2 ; 
 int /*<<< orphan*/  tree2_w ; 
 scalar_t__ view_mode ; 

__attribute__((used)) static void display_tree_part(void)
{
	if (tree2)
		gtk_tree_store_clear(tree2);
	if (view_mode == SINGLE_VIEW)
		display_tree(current);
	else if (view_mode == SPLIT_VIEW)
		display_tree(browsed);
	gtk_tree_view_expand_all(GTK_TREE_VIEW(tree2_w));
}