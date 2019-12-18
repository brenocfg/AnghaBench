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
typedef  int /*<<< orphan*/  GtkTreeView ;
typedef  int /*<<< orphan*/  GtkTreeSelection ;
typedef  int /*<<< orphan*/  GtkBuilder ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * GTK_TREE_VIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_selection_unselect_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_selection (int /*<<< orphan*/ *) ; 

void
ghb_clear_subtitle_selection(GtkBuilder *builder)
{
    GtkTreeView *tv;
    GtkTreeSelection *tsel;

    tv = GTK_TREE_VIEW(GHB_WIDGET(builder, "subtitle_list_view"));
    // Clear tree selection so that updates are not triggered
    // that cause a recursive attempt to clear the tree selection (crasher)
    tsel = gtk_tree_view_get_selection(tv);
    gtk_tree_selection_unselect_all(tsel);
}