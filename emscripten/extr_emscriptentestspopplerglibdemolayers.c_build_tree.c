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
typedef  int /*<<< orphan*/  gint ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  PopplerLayersIter ;
typedef  int /*<<< orphan*/  PopplerLayer ;
typedef  int /*<<< orphan*/  PopplerDocument ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_TREE_STORE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LAYERS_ENABLE_COLUMN ; 
 int /*<<< orphan*/  LAYERS_LAYER_COLUMN ; 
 int /*<<< orphan*/  LAYERS_RB_GROUP_COLUMN ; 
 int /*<<< orphan*/  LAYERS_SHOWTOGGLE_COLUMN ; 
 int /*<<< orphan*/  LAYERS_TITLE_COLUMN ; 
 int /*<<< orphan*/  LAYERS_VISIBILITY_COLUMN ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_markup_escape_text (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  poppler_layer_get_radio_button_group_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * poppler_layer_get_title (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_layer_is_visible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_layers_iter_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * poppler_layers_iter_get_child (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * poppler_layers_iter_get_layer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * poppler_layers_iter_get_title (int /*<<< orphan*/ *) ; 
 scalar_t__ poppler_layers_iter_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
build_tree (PopplerDocument   *document,
	    GtkTreeModel      *model,
	    GtkTreeIter       *parent,
	    PopplerLayersIter *iter)
{

	do {
		GtkTreeIter        tree_iter;
		PopplerLayersIter *child;
		PopplerLayer      *layer;
		gboolean           visible;
		gchar             *markup;
		gint               rb_group = 0;

		layer = poppler_layers_iter_get_layer (iter);
		if (layer) {
			markup = g_markup_escape_text (poppler_layer_get_title (layer), -1);
			visible = poppler_layer_is_visible (layer);
			rb_group = poppler_layer_get_radio_button_group_id (layer);
		} else {
			gchar *title;

			title = poppler_layers_iter_get_title (iter);
			markup = g_markup_escape_text (title, -1);
			g_free (title);

			visible = FALSE;
			layer = NULL;
		}

		gtk_tree_store_append (GTK_TREE_STORE (model), &tree_iter, parent);
		gtk_tree_store_set (GTK_TREE_STORE (model), &tree_iter,
				    LAYERS_TITLE_COLUMN, markup,
				    LAYERS_VISIBILITY_COLUMN, visible,
				    LAYERS_ENABLE_COLUMN, TRUE, /* FIXME */
				    LAYERS_SHOWTOGGLE_COLUMN, (layer != NULL),
				    LAYERS_RB_GROUP_COLUMN, rb_group,
				    LAYERS_LAYER_COLUMN, layer,
				    -1);
		if (layer)
			g_object_unref (layer);
		g_free (markup);

		child = poppler_layers_iter_get_child (iter);
		if (child)
			build_tree (document, model, &tree_iter, child);
		poppler_layers_iter_free (child);
	} while (poppler_layers_iter_next (iter));
}