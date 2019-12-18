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
typedef  int /*<<< orphan*/  hb_preset_index_t ;
typedef  int /*<<< orphan*/  GtkTreePath ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/ * gtk_tree_model_get_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_path_free (int /*<<< orphan*/ *) ; 
 int gtk_tree_path_get_depth (int /*<<< orphan*/ *) ; 
 int* gtk_tree_path_get_indices (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_preset_index_init (int*,int) ; 

hb_preset_index_t*
ghb_tree_get_index(GtkTreeModel *store, GtkTreeIter *iter)
{
    GtkTreePath       *treepath;
    int               *indices, len;
    hb_preset_index_t *path;

    treepath = gtk_tree_model_get_path(store, iter);
    indices  = gtk_tree_path_get_indices(treepath);
    len      = gtk_tree_path_get_depth(treepath);
    path     = hb_preset_index_init(indices, len);
    gtk_tree_path_free(treepath);

    return path;
}