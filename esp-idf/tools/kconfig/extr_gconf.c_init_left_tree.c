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
typedef  int /*<<< orphan*/  GtkTreeViewColumn ;
typedef  int /*<<< orphan*/  GtkTreeView ;
typedef  int /*<<< orphan*/  GtkTreeSelection ;
typedef  int /*<<< orphan*/  GtkCellRenderer ;

/* Variables and functions */
 int /*<<< orphan*/  COL_BTNACT ; 
 int /*<<< orphan*/  COL_BTNINC ; 
 int /*<<< orphan*/  COL_BTNRAD ; 
 int /*<<< orphan*/  COL_BTNVIS ; 
 int /*<<< orphan*/  COL_COLOR ; 
 int /*<<< orphan*/  COL_OPTION ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_SELECTION_SINGLE ; 
 int /*<<< orphan*/ * GTK_TREE_VIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_TREE_VIEW_COLUMN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * gtk_cell_renderer_text_new () ; 
 int /*<<< orphan*/ * gtk_cell_renderer_toggle_new () ; 
 int /*<<< orphan*/  gtk_tree_selection_set_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_append_column (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_column_new () ; 
 int /*<<< orphan*/  gtk_tree_view_column_pack_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_column_set_attributes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gtk_tree_view_column_set_title (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_selection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_view_set_headers_visible (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_set_model (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_set_rules_hint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_realize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  model1 ; 
 int /*<<< orphan*/  tree1_w ; 

void init_left_tree(void)
{
	GtkTreeView *view = GTK_TREE_VIEW(tree1_w);
	GtkCellRenderer *renderer;
	GtkTreeSelection *sel;
	GtkTreeViewColumn *column;

	gtk_tree_view_set_model(view, model1);
	gtk_tree_view_set_headers_visible(view, TRUE);
	gtk_tree_view_set_rules_hint(view, TRUE);

	column = gtk_tree_view_column_new();
	gtk_tree_view_append_column(view, column);
	gtk_tree_view_column_set_title(column, _("Options"));

	renderer = gtk_cell_renderer_toggle_new();
	gtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(column),
					renderer, FALSE);
	gtk_tree_view_column_set_attributes(GTK_TREE_VIEW_COLUMN(column),
					    renderer,
					    "active", COL_BTNACT,
					    "inconsistent", COL_BTNINC,
					    "visible", COL_BTNVIS,
					    "radio", COL_BTNRAD, NULL);
	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(column),
					renderer, FALSE);
	gtk_tree_view_column_set_attributes(GTK_TREE_VIEW_COLUMN(column),
					    renderer,
					    "text", COL_OPTION,
					    "foreground-gdk",
					    COL_COLOR, NULL);

	sel = gtk_tree_view_get_selection(view);
	gtk_tree_selection_set_mode(sel, GTK_SELECTION_SINGLE);
	gtk_widget_realize(tree1_w);
}