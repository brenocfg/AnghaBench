#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gint ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int gboolean ;
struct TYPE_4__ {int /*<<< orphan*/  treeview; } ;
typedef  int /*<<< orphan*/  PopplerLayer ;
typedef  TYPE_1__ PgdLayersDemo ;
typedef  int /*<<< orphan*/  GtkTreePath ;
typedef  int /*<<< orphan*/  GtkTreeModelForeachFunc ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  scalar_t__ GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkCellRendererToggle ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TREE_STORE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TREE_VIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LAYERS_LAYER_COLUMN ; 
 int /*<<< orphan*/  LAYERS_VISIBILITY_COLUMN ; 
 scalar_t__ clear_rb_group ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_model_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  gtk_tree_model_get_iter (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_path_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_path_new_from_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_set (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_model (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_layers_viewer_queue_redraw (TYPE_1__*) ; 
 scalar_t__ poppler_layer_get_radio_button_group_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_layer_hide (int /*<<< orphan*/ *) ; 
 scalar_t__ poppler_layer_is_parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_layer_show (int /*<<< orphan*/ *) ; 
 scalar_t__ update_kids ; 

__attribute__((used)) static void
pgd_layers_visibility_changed (GtkCellRendererToggle *cell,
			       gchar                 *path_str,
			       PgdLayersDemo         *demo)
{
	GtkTreeModel *model;
	GtkTreePath *path;
	GtkTreeIter iter;
	gboolean visible;
	PopplerLayer *layer;

	model = gtk_tree_view_get_model (GTK_TREE_VIEW (demo->treeview));

	path = gtk_tree_path_new_from_string (path_str);
	gtk_tree_model_get_iter (model, &iter, path);
	gtk_tree_model_get (model, &iter,
			    LAYERS_VISIBILITY_COLUMN, &visible,
			    LAYERS_LAYER_COLUMN, &layer,
			    -1);

	visible = !visible;
	visible ? poppler_layer_show (layer) : poppler_layer_hide (layer);

	if (visible) {
		gint rb_group;
		
		rb_group = poppler_layer_get_radio_button_group_id (layer);
		if (rb_group) {
			gtk_tree_model_foreach (model,
						(GtkTreeModelForeachFunc)clear_rb_group,
						&rb_group);
		}
	}
	
	gtk_tree_store_set (GTK_TREE_STORE (model), &iter,
			    LAYERS_VISIBILITY_COLUMN, visible,
			    -1);
	
	if (poppler_layer_is_parent (layer)) {
		gtk_tree_model_foreach (model,
					(GtkTreeModelForeachFunc)update_kids,
					&iter);
	}

	pgd_layers_viewer_queue_redraw (demo);

	gtk_tree_path_free (path);
	g_object_unref (layer);
}