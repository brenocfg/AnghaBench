#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
struct TYPE_8__ {scalar_t__ depth; } ;
typedef  TYPE_2__ hb_preset_index_t ;
typedef  int /*<<< orphan*/  GtkTreeView ;
typedef  int /*<<< orphan*/  GtkTreeStore ;
typedef  int /*<<< orphan*/  GtkTreePath ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GTK_TREE_STORE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GTK_TREE_VIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/ * ghb_tree_path_new_from_index (TYPE_2__*) ; 
 scalar_t__ gtk_tree_model_get_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_path_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int) ; 
 int /*<<< orphan*/  gtk_tree_view_get_model (int /*<<< orphan*/ *) ; 
 TYPE_2__* hb_presets_get_default_index () ; 

void
ghb_presets_list_show_default(signal_user_data_t *ud)
{
    hb_preset_index_t *path;

    path = hb_presets_get_default_index();
    if (path == NULL || path->depth == 0)
        return;

    GtkTreeView  *treeview;
    GtkTreeStore *store;
    GtkTreePath  *treepath;
    GtkTreeIter   iter;

    treeview = GTK_TREE_VIEW(GHB_WIDGET(ud->builder, "presets_list"));
    store    = GTK_TREE_STORE(gtk_tree_view_get_model(treeview));
    treepath = ghb_tree_path_new_from_index(path);
    if (treepath)
    {
        if (gtk_tree_model_get_iter(GTK_TREE_MODEL(store), &iter, treepath))
        {
            gtk_tree_store_set(store, &iter,
                        1, 800,
                        2, 2 ,
                        -1);
        }
        gtk_tree_path_free(treepath);
    }
    free(path);
}