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
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GtkTreePath ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_TREE_STORE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LAYERS_ENABLE_COLUMN ; 
 int /*<<< orphan*/  LAYERS_VISIBILITY_COLUMN ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ gtk_tree_store_is_ancestor (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static gboolean
update_kids (GtkTreeModel *model,
	     GtkTreePath  *path,
	     GtkTreeIter  *iter,
	     GtkTreeIter  *parent)
{
	if (gtk_tree_store_is_ancestor (GTK_TREE_STORE (model), parent, iter)) {
		gboolean visible;

		gtk_tree_model_get (model, parent,
				    LAYERS_VISIBILITY_COLUMN, &visible,
				    -1);
		gtk_tree_store_set (GTK_TREE_STORE (model), iter,
				    LAYERS_ENABLE_COLUMN, visible,
				    -1);
	}

	return FALSE;
}