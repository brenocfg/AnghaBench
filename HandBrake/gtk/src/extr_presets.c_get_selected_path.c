#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  hb_preset_index_t ;
typedef  int /*<<< orphan*/  GtkTreeView ;
typedef  int /*<<< orphan*/  GtkTreeSelection ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * GTK_TREE_VIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ghb_tree_get_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_tree_selection_get_selected (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_selection (int /*<<< orphan*/ *) ; 

hb_preset_index_t *
get_selected_path(signal_user_data_t *ud)
{
    GtkTreeView      *treeview;
    GtkTreeSelection *selection;
    GtkTreeModel     *store;
    GtkTreeIter       iter;

    treeview  = GTK_TREE_VIEW(GHB_WIDGET(ud->builder, "presets_list"));
    selection = gtk_tree_view_get_selection(treeview);
    if (gtk_tree_selection_get_selected(selection, &store, &iter))
    {
        return ghb_tree_get_index(store, &iter);
    }
    return NULL;
}