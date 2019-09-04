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
struct TYPE_3__ {int /*<<< orphan*/  field_view; } ;
typedef  int /*<<< orphan*/  PopplerFormField ;
typedef  TYPE_1__ PgdFormsDemo ;
typedef  int /*<<< orphan*/  GtkTreeSelection ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  FORMS_FIELD_COLUMN ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 scalar_t__ gtk_tree_selection_get_selected (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_form_field_view_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_forms_selection_changed (GtkTreeSelection *treeselection,
			     PgdFormsDemo     *demo)
{
	GtkTreeModel *model;
	GtkTreeIter   iter;

	if (gtk_tree_selection_get_selected (treeselection, &model, &iter)) {
		PopplerFormField *field;

		gtk_tree_model_get (model, &iter,
				    FORMS_FIELD_COLUMN, &field,
				    -1);
		pgd_form_field_view_set_field (demo->field_view, field);
		g_object_unref (field);
	}
}