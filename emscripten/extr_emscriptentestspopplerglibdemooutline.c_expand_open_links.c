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
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  GtkTreeView ;
typedef  int /*<<< orphan*/  GtkTreePath ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OUTLINE_EXPAND_COLUMN ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/ * gtk_tree_model_get_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_tree_model_iter_children (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_tree_model_iter_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_path_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_view_expand_row (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
expand_open_links (GtkTreeView  *tree_view,
		   GtkTreeModel *model,
		   GtkTreeIter  *parent)
{
	GtkTreeIter iter;
	gboolean    expand;

	if (gtk_tree_model_iter_children (model, &iter, parent)) {
		do {
			gtk_tree_model_get (model, &iter,
					    OUTLINE_EXPAND_COLUMN, &expand,
					    -1);
			if (expand) {
				GtkTreePath *path;

				path = gtk_tree_model_get_path (model, &iter);
				gtk_tree_view_expand_row (tree_view, path, FALSE);
				gtk_tree_path_free (path);
			}

			expand_open_links (tree_view, model, &iter);
		} while (gtk_tree_model_iter_next (model, &iter));
	}
}