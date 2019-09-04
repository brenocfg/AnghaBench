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
typedef  int /*<<< orphan*/  GtkTreeViewColumn ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkCellRenderer ;

/* Variables and functions */
 int /*<<< orphan*/  FONTS_DETAILS_COLUMN ; 
 int /*<<< orphan*/  FONTS_NAME_COLUMN ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_object_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 char* g_strdup_printf (char*,char*,...) ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ ,char**,int) ; 

__attribute__((used)) static void
pdg_fonts_cell_data_func (GtkTreeViewColumn *col,
			  GtkCellRenderer   *renderer,
			  GtkTreeModel      *model,
			  GtkTreeIter       *iter,
			  gpointer           user_data)
{
	char *name;
	char *details;
	char *markup;

	gtk_tree_model_get (model, iter,
			    FONTS_NAME_COLUMN, &name,
			    FONTS_DETAILS_COLUMN, &details,
			    -1);

	if (details) {
		markup = g_strdup_printf ("<b><big>%s</big></b>\n<small>%s</small>",
					  name, details);
	} else {
		markup = g_strdup_printf ("<b><big>%s</big></b>", name);
	}

	g_object_set (renderer, "markup", markup, NULL);

	g_free (markup);
	g_free (details);
	g_free (name);
}