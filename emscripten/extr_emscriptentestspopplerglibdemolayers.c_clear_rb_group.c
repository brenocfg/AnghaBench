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
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GtkTreePath ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_TREE_STORE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LAYERS_RB_GROUP_COLUMN ; 
 int /*<<< orphan*/  LAYERS_VISIBILITY_COLUMN ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  gtk_tree_store_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static gboolean
clear_rb_group (GtkTreeModel *model,
		GtkTreePath  *path,
		GtkTreeIter  *iter,
		gint         *rb_group)
{
	gint group;
	
	gtk_tree_model_get (model, iter,
			    LAYERS_RB_GROUP_COLUMN, &group,
			    -1);
	
	if (group == *rb_group) {
		gtk_tree_store_set (GTK_TREE_STORE (model), iter,
				    LAYERS_VISIBILITY_COLUMN, FALSE,
				    -1);
	}
	
	return FALSE;
}