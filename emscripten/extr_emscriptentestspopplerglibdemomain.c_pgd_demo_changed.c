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
typedef  int /*<<< orphan*/  gint ;
typedef  int /*<<< orphan*/  GtkTreeSelection ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkNotebook ;

/* Variables and functions */
 int /*<<< orphan*/  PGD_NPAGE_COLUMN ; 
 int /*<<< orphan*/  gtk_notebook_set_current_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ gtk_tree_selection_get_selected (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_demo_changed (GtkTreeSelection *selection,
		  GtkNotebook      *notebook)
{
	GtkTreeModel *model;
	GtkTreeIter   iter;

	if (gtk_tree_selection_get_selected (selection, &model, &iter)) {
		gint n_page;
		
		gtk_tree_model_get (model, &iter,
				    PGD_NPAGE_COLUMN, &n_page,
				    -1);
		gtk_notebook_set_current_page (notebook, n_page);
	}
}