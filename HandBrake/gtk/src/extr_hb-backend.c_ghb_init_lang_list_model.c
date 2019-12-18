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
typedef  int /*<<< orphan*/  GtkTreeStore ;
typedef  int /*<<< orphan*/  GtkCellRenderer ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TREE_VIEW_COLUMN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_TYPE_INT ; 
 int /*<<< orphan*/  G_TYPE_STRING ; 
 int /*<<< orphan*/ * gtk_cell_renderer_text_new () ; 
 int /*<<< orphan*/ * gtk_tree_store_new (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_append_column (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_column_add_attribute (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_tree_view_column_new () ; 
 int /*<<< orphan*/  gtk_tree_view_column_pack_start (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_set_model (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ghb_init_lang_list_model(GtkTreeView *tv)
{
    GtkTreeViewColumn * column;
    GtkTreeStore      * ts;
    GtkCellRenderer   * lang_cell;

    // Store contains:
    // 0 - Language string to display
    // 1 - Index of language in the libhb language list
    ts = gtk_tree_store_new(2, G_TYPE_STRING, G_TYPE_INT);
    gtk_tree_view_set_model(tv, GTK_TREE_MODEL(ts));

    lang_cell = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new();
    gtk_tree_view_column_pack_start(column, lang_cell, FALSE);
    gtk_tree_view_column_add_attribute(column, lang_cell, "markup", 0);
    gtk_tree_view_append_column(tv, GTK_TREE_VIEW_COLUMN(column));
}