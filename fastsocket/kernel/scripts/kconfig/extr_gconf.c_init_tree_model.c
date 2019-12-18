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
typedef  int gint ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  COL_NUMBER ; 
 int /*<<< orphan*/  GDK_TYPE_COLOR ; 
 int /*<<< orphan*/  GDK_TYPE_PIXBUF ; 
 void* GTK_TREE_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_TYPE_BOOLEAN ; 
 int /*<<< orphan*/  G_TYPE_POINTER ; 
 int /*<<< orphan*/  G_TYPE_STRING ; 
 scalar_t__ g_malloc (int) ; 
 int /*<<< orphan*/  gtk_tree_store_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* model1 ; 
 void* model2 ; 
 int /*<<< orphan*/ ** parents ; 
 int /*<<< orphan*/  tree ; 
 int /*<<< orphan*/  tree1 ; 
 int /*<<< orphan*/  tree2 ; 

void init_tree_model(void)
{
	gint i;

	tree = tree2 = gtk_tree_store_new(COL_NUMBER,
					  G_TYPE_STRING, G_TYPE_STRING,
					  G_TYPE_STRING, G_TYPE_STRING,
					  G_TYPE_STRING, G_TYPE_STRING,
					  G_TYPE_POINTER, GDK_TYPE_COLOR,
					  G_TYPE_BOOLEAN, GDK_TYPE_PIXBUF,
					  G_TYPE_BOOLEAN, G_TYPE_BOOLEAN,
					  G_TYPE_BOOLEAN, G_TYPE_BOOLEAN,
					  G_TYPE_BOOLEAN);
	model2 = GTK_TREE_MODEL(tree2);

	for (parents[0] = NULL, i = 1; i < 256; i++)
		parents[i] = (GtkTreeIter *) g_malloc(sizeof(GtkTreeIter));

	tree1 = gtk_tree_store_new(COL_NUMBER,
				   G_TYPE_STRING, G_TYPE_STRING,
				   G_TYPE_STRING, G_TYPE_STRING,
				   G_TYPE_STRING, G_TYPE_STRING,
				   G_TYPE_POINTER, GDK_TYPE_COLOR,
				   G_TYPE_BOOLEAN, GDK_TYPE_PIXBUF,
				   G_TYPE_BOOLEAN, G_TYPE_BOOLEAN,
				   G_TYPE_BOOLEAN, G_TYPE_BOOLEAN,
				   G_TYPE_BOOLEAN);
	model1 = GTK_TREE_MODEL(tree1);
}