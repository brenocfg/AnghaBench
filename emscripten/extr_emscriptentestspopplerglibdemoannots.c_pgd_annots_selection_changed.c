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
struct TYPE_3__ {int /*<<< orphan*/  annot_view; } ;
typedef  int /*<<< orphan*/  PopplerAnnot ;
typedef  TYPE_1__ PgdAnnotsDemo ;
typedef  int /*<<< orphan*/  GtkTreeSelection ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  ANNOTS_COLUMN ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 scalar_t__ gtk_tree_selection_get_selected (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_annot_view_set_annot (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_annots_selection_changed (GtkTreeSelection *treeselection,
                              PgdAnnotsDemo    *demo)
{
    GtkTreeModel *model;
    GtkTreeIter   iter;

    if (gtk_tree_selection_get_selected (treeselection, &model, &iter)) {
        PopplerAnnot *annot;

        gtk_tree_model_get (model, &iter,
                            ANNOTS_COLUMN, &annot,
                           -1);
        pgd_annot_view_set_annot (demo->annot_view, annot);
        g_object_unref (annot);
    }
}