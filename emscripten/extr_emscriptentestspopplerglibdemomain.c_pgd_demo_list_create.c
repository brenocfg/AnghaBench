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
typedef  size_t gint ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkListStore ;
typedef  int /*<<< orphan*/  GtkCellRenderer ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TREE_VIEW (int /*<<< orphan*/ *) ; 
 size_t G_N_ELEMENTS (TYPE_1__*) ; 
 int /*<<< orphan*/  G_TYPE_INT ; 
 int /*<<< orphan*/  G_TYPE_POINTER ; 
 int /*<<< orphan*/  G_TYPE_STRING ; 
 int /*<<< orphan*/  N_COLUMNS ; 
 int /*<<< orphan*/  PGD_NPAGE_COLUMN ; 
 int /*<<< orphan*/  PGD_TITLE_COLUMN ; 
 TYPE_1__* demo_list ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_cell_renderer_text_new () ; 
 int /*<<< orphan*/  gtk_list_store_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_list_store_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_list_store_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  gtk_tree_view_insert_column_with_attributes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_new_with_model (int /*<<< orphan*/ ) ; 

__attribute__((used)) static GtkWidget *
pgd_demo_list_create (void)
{
	GtkWidget       *treeview;
	GtkListStore    *model;
	GtkCellRenderer *renderer;
	gint             i;

	model = gtk_list_store_new (N_COLUMNS,
				    G_TYPE_STRING,
				    G_TYPE_INT,
				    G_TYPE_POINTER);
	treeview = gtk_tree_view_new_with_model (GTK_TREE_MODEL (model));

	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeview),
						     0, "Demos",
						     renderer,
						     "text", PGD_TITLE_COLUMN,
						     NULL);
	
	for (i = 0; i < G_N_ELEMENTS (demo_list); i++) {
		GtkTreeIter iter;

		gtk_list_store_append (model, &iter);
		gtk_list_store_set (model, &iter,
				    PGD_TITLE_COLUMN, demo_list[i].name,
				    PGD_NPAGE_COLUMN, i,
				    -1);
	}

	g_object_unref (model);
	
	return treeview;
}