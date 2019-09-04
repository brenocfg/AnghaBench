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
struct TYPE_3__ {int /*<<< orphan*/  action_view; } ;
typedef  int /*<<< orphan*/  PopplerAction ;
typedef  TYPE_1__ PgdLinksDemo ;
typedef  int /*<<< orphan*/  GtkTreeSelection ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  LINKS_ACTION_COLUMN ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 scalar_t__ gtk_tree_selection_get_selected (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_action_view_set_action (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_links_selection_changed (GtkTreeSelection *treeselection,
			     PgdLinksDemo     *demo)
{
	GtkTreeModel *model;
	GtkTreeIter   iter;

	if (gtk_tree_selection_get_selected (treeselection, &model, &iter)) {
		PopplerAction *action;

		gtk_tree_model_get (model, &iter,
				    LINKS_ACTION_COLUMN, &action,
				    -1);
		pgd_action_view_set_action (demo->action_view, action);
	}
}