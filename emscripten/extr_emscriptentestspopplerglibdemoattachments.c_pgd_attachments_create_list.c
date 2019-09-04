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
 int /*<<< orphan*/  ATTACHMENTS_CTIME_COLUMN ; 
 int /*<<< orphan*/  ATTACHMENTS_DESCRIPTION_COLUMN ; 
 int /*<<< orphan*/  ATTACHMENTS_MTIME_COLUMN ; 
 int /*<<< orphan*/  ATTACHMENTS_NAME_COLUMN ; 
 int /*<<< orphan*/  ATTACHMENTS_SIZE_COLUMN ; 
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TREE_VIEW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PANGO_ELLIPSIZE_END ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_object_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_cell_renderer_text_new () ; 
 int /*<<< orphan*/ * gtk_tree_view_get_column (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_tree_view_insert_column_with_attributes (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_new_with_model (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_set_headers_visible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_set_rules_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static GtkWidget *
pgd_attachments_create_list (GtkTreeModel *model)
{
	GtkWidget       *treeview;
	GtkCellRenderer *renderer;
	
	treeview = gtk_tree_view_new_with_model (GTK_TREE_MODEL (model));
	gtk_tree_view_set_headers_visible (GTK_TREE_VIEW (treeview), TRUE);
	gtk_tree_view_set_rules_hint (GTK_TREE_VIEW (treeview), TRUE);

	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeview),
						     0, "Name",
						     renderer,
						     "text", ATTACHMENTS_NAME_COLUMN,
						     NULL);
	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeview),
						     1, "Description",
						     renderer,
						     "text", ATTACHMENTS_DESCRIPTION_COLUMN,
						     NULL);
	g_object_set (G_OBJECT (renderer), "ellipsize", PANGO_ELLIPSIZE_END, NULL);
	g_object_set (G_OBJECT (gtk_tree_view_get_column (GTK_TREE_VIEW (treeview), 1)),
		      "expand", TRUE, NULL);
	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeview),
						     2, "Size",
						     renderer,
						     "text", ATTACHMENTS_SIZE_COLUMN,
						     NULL);
	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeview),
						     3, "Creation Date",
						     renderer,
						     "text", ATTACHMENTS_CTIME_COLUMN,
						     NULL);
	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeview),
						     4, "Modification Date",
						     renderer,
						     "text", ATTACHMENTS_MTIME_COLUMN,
						     NULL);
	return treeview;
}