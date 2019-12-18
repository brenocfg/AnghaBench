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
typedef  int /*<<< orphan*/  gint ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkTreeViewColumn ;
typedef  int /*<<< orphan*/  GtkTreeView ;
typedef  int /*<<< orphan*/  GtkTreePath ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  TYPE_1__ GdkEventButton ;

/* Variables and functions */
 int /*<<< orphan*/  COL_MENU ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GDK_2BUTTON_PRESS ; 
 int /*<<< orphan*/ * GTK_TREE_VIEW (int /*<<< orphan*/ *) ; 
 struct menu* browsed ; 
 struct menu* current ; 
 int /*<<< orphan*/  display_tree_part () ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct menu**,int) ; 
 int /*<<< orphan*/  gtk_tree_model_get_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_view_get_path_at_pos (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_view_set_cursor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_grab_focus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_realize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  model1 ; 
 int /*<<< orphan*/  toggle_sym_value (struct menu*) ; 
 int /*<<< orphan*/  tree2_w ; 

gboolean
on_treeview1_button_press_event(GtkWidget * widget,
				GdkEventButton * event, gpointer user_data)
{
	GtkTreeView *view = GTK_TREE_VIEW(widget);
	GtkTreePath *path;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	struct menu *menu;

	gint tx = (gint) event->x;
	gint ty = (gint) event->y;
	gint cx, cy;

	gtk_tree_view_get_path_at_pos(view, tx, ty, &path, &column, &cx,
				      &cy);
	if (path == NULL)
		return FALSE;

	gtk_tree_model_get_iter(model1, &iter, path);
	gtk_tree_model_get(model1, &iter, COL_MENU, &menu, -1);

	if (event->type == GDK_2BUTTON_PRESS) {
		toggle_sym_value(menu);
		current = menu;
		display_tree_part();
	} else {
		browsed = menu;
		display_tree_part();
	}

	gtk_widget_realize(tree2_w);
	gtk_tree_view_set_cursor(view, path, NULL, FALSE);
	gtk_widget_grab_focus(tree2_w);

	return FALSE;
}