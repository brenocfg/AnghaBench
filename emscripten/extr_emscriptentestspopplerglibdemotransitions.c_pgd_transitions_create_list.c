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
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkCellRenderer ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_SELECTION_NONE ; 
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TREE_VIEW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRANSITIONS_ALIGNMENT_COLUMN ; 
 int /*<<< orphan*/  TRANSITIONS_ANGLE_COLUMN ; 
 int /*<<< orphan*/  TRANSITIONS_DIRECTION_COLUMN ; 
 int /*<<< orphan*/  TRANSITIONS_DURATION_COLUMN ; 
 int /*<<< orphan*/  TRANSITIONS_PAGE_COLUMN ; 
 int /*<<< orphan*/  TRANSITIONS_RECTANGULAR_COLUMN ; 
 int /*<<< orphan*/  TRANSITIONS_SCALE_COLUMN ; 
 int /*<<< orphan*/  TRANSITIONS_TYPE_COLUMN ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * gtk_cell_renderer_text_new () ; 
 int /*<<< orphan*/  gtk_tree_selection_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_get_selection (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_insert_column_with_attributes (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_new_with_model (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_set_headers_visible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_set_rules_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static GtkWidget *
pgd_transitions_create_list (GtkTreeModel *model)
{
	GtkWidget       *treeview;
	GtkCellRenderer *renderer;
	
	treeview = gtk_tree_view_new_with_model (GTK_TREE_MODEL (model));
	gtk_tree_view_set_headers_visible (GTK_TREE_VIEW (treeview), TRUE);
	gtk_tree_view_set_rules_hint (GTK_TREE_VIEW (treeview), TRUE);
	gtk_tree_selection_set_mode (gtk_tree_view_get_selection (GTK_TREE_VIEW (treeview)),
				     GTK_SELECTION_NONE);

	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeview),
						     0, "Page",
						     renderer,
						     "text", TRANSITIONS_PAGE_COLUMN,
						     NULL);
	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeview),
						     1, "Type",
						     renderer,
						     "text", TRANSITIONS_TYPE_COLUMN,
						     NULL);
	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeview),
						     2, "Alignment",
						     renderer,
						     "text", TRANSITIONS_ALIGNMENT_COLUMN,
						     NULL);
	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeview),
						     3, "Direction",
						     renderer,
						     "text", TRANSITIONS_DIRECTION_COLUMN,
						     NULL);
	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeview),
						     4, "Duration",
						     renderer,
						     "text", TRANSITIONS_DURATION_COLUMN,
						     NULL);
	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeview),
						     5, "Angle",
						     renderer,
						     "text", TRANSITIONS_ANGLE_COLUMN,
						     NULL);
	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeview),
						     6, "Scale",
						     renderer,
						     "text", TRANSITIONS_SCALE_COLUMN,
						     NULL);
	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeview),
						     7, "Rectangular",
						     renderer,
						     "text", TRANSITIONS_RECTANGULAR_COLUMN,
						     NULL);
	return treeview;
}