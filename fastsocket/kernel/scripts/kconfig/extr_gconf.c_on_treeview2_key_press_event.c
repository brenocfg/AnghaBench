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
struct menu {int dummy; } ;
typedef  int /*<<< orphan*/  gpointer ;
typedef  int gint ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_3__ {scalar_t__ keyval; int /*<<< orphan*/  string; } ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkTreeViewColumn ;
typedef  int /*<<< orphan*/  GtkTreeView ;
typedef  int /*<<< orphan*/  GtkTreePath ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  TYPE_1__ GdkEventKey ;

/* Variables and functions */
 int /*<<< orphan*/  COL_MENU ; 
 int COL_MOD ; 
 int COL_NO ; 
 int COL_YES ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GDK_KP_Enter ; 
 scalar_t__ GDK_space ; 
 int /*<<< orphan*/ * GTK_TREE_VIEW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  change_sym_value (struct menu*,int) ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct menu**,int) ; 
 int /*<<< orphan*/  gtk_tree_model_get_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_view_collapse_row (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_view_expand_row (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_get_cursor (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 scalar_t__ gtk_tree_view_row_expanded (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  model2 ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * tree1_w ; 

gboolean
on_treeview2_key_press_event(GtkWidget * widget,
			     GdkEventKey * event, gpointer user_data)
{
	GtkTreeView *view = GTK_TREE_VIEW(widget);
	GtkTreePath *path;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	struct menu *menu;
	gint col;

	gtk_tree_view_get_cursor(view, &path, &column);
	if (path == NULL)
		return FALSE;

	if (event->keyval == GDK_space) {
		if (gtk_tree_view_row_expanded(view, path))
			gtk_tree_view_collapse_row(view, path);
		else
			gtk_tree_view_expand_row(view, path, FALSE);
		return TRUE;
	}
	if (event->keyval == GDK_KP_Enter) {
	}
	if (widget == tree1_w)
		return FALSE;

	gtk_tree_model_get_iter(model2, &iter, path);
	gtk_tree_model_get(model2, &iter, COL_MENU, &menu, -1);

	if (!strcasecmp(event->string, "n"))
		col = COL_NO;
	else if (!strcasecmp(event->string, "m"))
		col = COL_MOD;
	else if (!strcasecmp(event->string, "y"))
		col = COL_YES;
	else
		col = -1;
	change_sym_value(menu, col);

	return FALSE;
}