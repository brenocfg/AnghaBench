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
typedef  int /*<<< orphan*/  PopplerAction ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkTreeSelection ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  OUTLINE_ACTION_COLUMN ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 scalar_t__ gtk_tree_selection_get_selected (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_action_view_set_action (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_outline_selection_changed (GtkTreeSelection *treeselection,
			       GtkWidget        *action_view)
{
	GtkTreeModel *model;
	GtkTreeIter   iter;
	
	if (gtk_tree_selection_get_selected (treeselection, &model, &iter)) {
		PopplerAction *action;

		gtk_tree_model_get (model, &iter,
				    OUTLINE_ACTION_COLUMN, &action,
				    -1);
		pgd_action_view_set_action (action_view, action);
	}
}