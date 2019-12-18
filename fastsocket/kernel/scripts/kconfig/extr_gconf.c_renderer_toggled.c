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
struct menu {int dummy; } ;
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GtkTreeSelection ;
typedef  int /*<<< orphan*/  GtkTreePath ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkCellRendererToggle ;

/* Variables and functions */
 int /*<<< orphan*/  COL_MENU ; 
 int /*<<< orphan*/  GTK_TREE_VIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct menu**,int) ; 
 int /*<<< orphan*/  gtk_tree_model_get_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_model_get_path (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_tree_path_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_path_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_path_new_from_string (int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_tree_selection_get_selected (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_selection (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  model2 ; 
 int /*<<< orphan*/  toggle_sym_value (struct menu*) ; 
 int /*<<< orphan*/  tree2_w ; 

__attribute__((used)) static void renderer_toggled(GtkCellRendererToggle * cell,
			     gchar * path_string, gpointer user_data)
{
	GtkTreePath *path, *sel_path = NULL;
	GtkTreeIter iter, sel_iter;
	GtkTreeSelection *sel;
	struct menu *menu;

	path = gtk_tree_path_new_from_string(path_string);
	if (!gtk_tree_model_get_iter(model2, &iter, path))
		return;

	sel = gtk_tree_view_get_selection(GTK_TREE_VIEW(tree2_w));
	if (gtk_tree_selection_get_selected(sel, NULL, &sel_iter))
		sel_path = gtk_tree_model_get_path(model2, &sel_iter);
	if (!sel_path)
		goto out1;
	if (gtk_tree_path_compare(path, sel_path))
		goto out2;

	gtk_tree_model_get(model2, &iter, COL_MENU, &menu, -1);
	toggle_sym_value(menu);

      out2:
	gtk_tree_path_free(sel_path);
      out1:
	gtk_tree_path_free(path);
}