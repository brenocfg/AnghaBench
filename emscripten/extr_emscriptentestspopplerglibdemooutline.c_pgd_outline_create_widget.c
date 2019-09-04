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
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  PopplerDocument ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkTreeSelection ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkCellRenderer ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ *) ; 
 scalar_t__ GTK_IS_TREE_STORE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_PANED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_POLICY_AUTOMATIC ; 
 int /*<<< orphan*/  GTK_SCROLLED_WINDOW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_SELECTION_NONE ; 
 int /*<<< orphan*/  GTK_TREE_VIEW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OUTLINE_ACTION_TYPE_COLUMN ; 
 int /*<<< orphan*/  OUTLINE_TITLE_COLUMN ; 
 int /*<<< orphan*/  PANGO_ELLIPSIZE_END ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  expand_open_links (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_cell_renderer_text_new () ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_hpaned_new () ; 
 int /*<<< orphan*/  gtk_paned_add1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_paned_add2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_paned_set_position (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * gtk_scrolled_window_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_scrolled_window_set_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_selection_set_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_column (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_selection (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_insert_column_with_attributes (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_new_with_model (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pgd_action_view_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pgd_outline_create_model (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_outline_selection_changed ; 

GtkWidget *
pgd_outline_create_widget (PopplerDocument *document)
{
	GtkWidget        *swindow;
	GtkWidget        *treeview;
	GtkTreeModel     *model;
	GtkCellRenderer  *renderer;
	GtkTreeSelection *selection;
	GtkWidget        *hpaned, *action;

	hpaned = gtk_hpaned_new ();

	action = pgd_action_view_new (document);
	
	swindow = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (swindow),
					GTK_POLICY_AUTOMATIC,
					GTK_POLICY_AUTOMATIC);

	model = pgd_outline_create_model (document);
	treeview = gtk_tree_view_new_with_model (model);
	g_object_unref (model);

	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeview),
						     0, "Title",
						     renderer,
						     "markup", OUTLINE_TITLE_COLUMN,
						     NULL);
	g_object_set (G_OBJECT (renderer), "ellipsize", PANGO_ELLIPSIZE_END, NULL);
	g_object_set (G_OBJECT (gtk_tree_view_get_column (GTK_TREE_VIEW (treeview), 0)),
		      "expand", TRUE, NULL);

	if (GTK_IS_TREE_STORE (model)) {
		renderer = gtk_cell_renderer_text_new ();
		gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeview),
							     1, "Action Type",
							     renderer,
							     "text", OUTLINE_ACTION_TYPE_COLUMN,
							     NULL);

		expand_open_links (GTK_TREE_VIEW (treeview), model, NULL);

		selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (treeview));
		g_signal_connect (G_OBJECT (selection), "changed",
				  G_CALLBACK (pgd_outline_selection_changed),
				  (gpointer)action);
	} else {
		gtk_tree_selection_set_mode (gtk_tree_view_get_selection (GTK_TREE_VIEW (treeview)),
					     GTK_SELECTION_NONE);
	}

	gtk_container_add (GTK_CONTAINER (swindow), treeview);
	gtk_widget_show (treeview);

	gtk_paned_add1 (GTK_PANED (hpaned), swindow);
	gtk_widget_show (swindow);

	gtk_paned_add2 (GTK_PANED (hpaned), action);
	gtk_widget_show (action);

	gtk_paned_set_position (GTK_PANED (hpaned), 300);

	return hpaned;
}