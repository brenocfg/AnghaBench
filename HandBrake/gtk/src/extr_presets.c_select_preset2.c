#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  app; int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
struct TYPE_10__ {scalar_t__ depth; } ;
typedef  TYPE_2__ hb_preset_index_t ;
typedef  int /*<<< orphan*/  GtkTreeView ;
typedef  int /*<<< orphan*/  GtkTreeSelection ;
typedef  int /*<<< orphan*/  GtkTreePath ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GSimpleAction ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * GTK_TREE_VIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_ACTION_MAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * G_SIMPLE_ACTION (int /*<<< orphan*/ ) ; 
 int HB_PRESET_TYPE_CUSTOM ; 
 int /*<<< orphan*/  g_action_map_lookup_action (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_simple_action_set_enabled (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ghb_tree_path_new_from_index (TYPE_2__*) ; 
 scalar_t__ gtk_tree_model_get_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_tree_model_get_iter_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_path_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_selection_select_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_view_expand_to_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_model (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_selection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_view_scroll_to_cell (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int preset_get_type (TYPE_2__*) ; 
 int /*<<< orphan*/  set_preset_menu_button_label (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static void
select_preset2(signal_user_data_t *ud, hb_preset_index_t *path)
{
    GtkTreeView      *treeview;
    GtkTreeSelection *selection;
    GtkTreeModel     *store;
    GtkTreeIter       iter;
    GtkTreePath      *treepath;

    if (path == NULL || path->depth == 0)
        return;

    treeview  = GTK_TREE_VIEW(GHB_WIDGET(ud->builder, "presets_list"));
    selection = gtk_tree_view_get_selection (treeview);
    store     = gtk_tree_view_get_model (treeview);
    treepath  = ghb_tree_path_new_from_index(path);
    if (treepath != NULL)
    {
        gtk_tree_view_expand_to_path(treeview, treepath);
        if (gtk_tree_model_get_iter(store, &iter, treepath))
        {
            gtk_tree_selection_select_iter(selection, &iter);
        }
        else
        {
            if (gtk_tree_model_get_iter_first(store, &iter))
                gtk_tree_selection_select_iter(selection, &iter);
        }
        // Make the selection visible in scroll window if it is not.
        gtk_tree_view_scroll_to_cell(treeview, treepath, NULL, FALSE, 0, 0);
        gtk_tree_path_free(treepath);
    }
    set_preset_menu_button_label(ud, path);

    int type = preset_get_type(path);
    GSimpleAction * action;

    action = G_SIMPLE_ACTION(g_action_map_lookup_action(
                             G_ACTION_MAP(ud->app), "preset-rename"));
    g_simple_action_set_enabled(action, type == HB_PRESET_TYPE_CUSTOM);
    action = G_SIMPLE_ACTION(g_action_map_lookup_action(
                             G_ACTION_MAP(ud->app), "preset-save"));
    g_simple_action_set_enabled(action, type == HB_PRESET_TYPE_CUSTOM);
}