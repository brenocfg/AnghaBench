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
typedef  int /*<<< orphan*/  gpointer ;
struct TYPE_3__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ PgdTextDemo ;
typedef  int /*<<< orphan*/  GtkTreeSelection ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkTextIter ;

/* Variables and functions */
 int /*<<< orphan*/  GPOINTER_TO_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEXT_OFFPTR_COLUMN ; 
 int /*<<< orphan*/  gtk_text_buffer_get_iter_at_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_text_buffer_select_range (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_text_iter_forward_char (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ gtk_tree_selection_get_selected (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_text_selection_changed (GtkTreeSelection *treeselection,
			    PgdTextDemo      *demo)
{
	GtkTreeModel *model;
	GtkTreeIter   iter;

	if (gtk_tree_selection_get_selected (treeselection, &model, &iter)) {
		gpointer    offset;
		GtkTextIter begin_iter, end_iter;

		gtk_tree_model_get (model, &iter,
				    TEXT_OFFPTR_COLUMN, &offset,
				    -1);

		gtk_text_buffer_get_iter_at_offset (demo->buffer, &begin_iter, GPOINTER_TO_INT (offset));
		end_iter = begin_iter;
		gtk_text_iter_forward_char (&end_iter);
		gtk_text_buffer_select_range (demo->buffer, &begin_iter, &end_iter);
	}
}