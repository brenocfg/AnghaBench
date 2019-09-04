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
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  PopplerLayersIter ;
typedef  int /*<<< orphan*/  PopplerDocument ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_LIST_STORE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GTK_TREE_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_TYPE_BOOLEAN ; 
 int /*<<< orphan*/  G_TYPE_INT ; 
 int /*<<< orphan*/  G_TYPE_OBJECT ; 
 int /*<<< orphan*/  G_TYPE_STRING ; 
 int /*<<< orphan*/  N_COLUMNS ; 
 int /*<<< orphan*/  build_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup_printf (char*,char*) ; 
 int /*<<< orphan*/  gtk_list_store_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_new (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_list_store_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gtk_tree_store_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poppler_layers_iter_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * poppler_layers_iter_new (int /*<<< orphan*/ *) ; 

GtkTreeModel *
pgd_layers_create_model (PopplerDocument *document)
{
	GtkTreeModel     *model;
	PopplerLayersIter *iter;

	iter = poppler_layers_iter_new (document);
	if (iter) {
		model = GTK_TREE_MODEL (
			gtk_tree_store_new (N_COLUMNS,
					    G_TYPE_STRING, 
					    G_TYPE_BOOLEAN,
					    G_TYPE_BOOLEAN,
					    G_TYPE_BOOLEAN,
					    G_TYPE_INT,
					    G_TYPE_OBJECT));
		build_tree (document, model, NULL, iter);
		poppler_layers_iter_free (iter);
	} else {
		GtkTreeIter tree_iter;
		gchar      *markup;
		
		model = GTK_TREE_MODEL (gtk_list_store_new (1, G_TYPE_STRING));
		gtk_list_store_append (GTK_LIST_STORE (model), &tree_iter);
		markup = g_strdup_printf ("<span size=\"larger\" style=\"italic\">%s</span>",
					  "The document doesn't contain layers");
		gtk_list_store_set (GTK_LIST_STORE (model), &tree_iter,
				    0, markup, -1);
		g_free (markup);
	}

	return model;
}