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
struct TYPE_4__ {int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  GtkTreeViewColumn ;
typedef  int /*<<< orphan*/  GtkTreeView ;
typedef  int /*<<< orphan*/  GtkTreeStore ;
typedef  int /*<<< orphan*/  GtkTreeSelection ;
typedef  int /*<<< orphan*/  GtkCellRenderer ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GTK_TREE_VIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_TREE_VIEW_COLUMN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_TYPE_FLOAT ; 
 int /*<<< orphan*/  G_TYPE_STRING ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  audio_edit_clicked_cb ; 
 int /*<<< orphan*/  audio_list_selection_changed_cb ; 
 int /*<<< orphan*/  audio_remove_clicked_cb ; 
 int /*<<< orphan*/ * custom_cell_renderer_button_new () ; 
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * gtk_cell_renderer_text_new () ; 
 int /*<<< orphan*/ * gtk_tree_store_new (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_append_column (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_column_add_attribute (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * gtk_tree_view_column_new () ; 
 int /*<<< orphan*/ * gtk_tree_view_column_new_with_attributes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_view_column_pack_start (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_column_set_expand (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_column_set_max_width (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gtk_tree_view_column_set_spacing (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gtk_tree_view_column_set_title (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_selection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_view_set_model (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bind_audio_tree_model(signal_user_data_t *ud)
{
    GtkCellRenderer *source_cell;
    GtkCellRenderer *arrow_cell;
    GtkCellRenderer *output_cell;
    GtkCellRenderer *edit_cell;
    GtkCellRenderer *delete_cell;
    GtkTreeViewColumn *column;
    GtkTreeStore *treestore;
    GtkTreeView  *treeview;
    GtkTreeSelection *selection;

    g_debug("bind_audio_tree_model()\n");
    treeview = GTK_TREE_VIEW(GHB_WIDGET(ud->builder, "audio_list_view"));
    selection = gtk_tree_view_get_selection(treeview);
    treestore = gtk_tree_store_new(6, G_TYPE_STRING, G_TYPE_STRING,
                                      G_TYPE_STRING, G_TYPE_STRING,
                                      G_TYPE_STRING, G_TYPE_FLOAT);
    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(treestore));

    source_cell = gtk_cell_renderer_text_new();
    arrow_cell = gtk_cell_renderer_text_new();
    output_cell = gtk_cell_renderer_text_new();
    edit_cell = custom_cell_renderer_button_new();
    delete_cell = custom_cell_renderer_button_new();

    column = gtk_tree_view_column_new();
    gtk_tree_view_column_set_spacing(column, 12);
    gtk_tree_view_column_set_title(column, _("Track Information"));
    gtk_tree_view_column_pack_start(column, source_cell, FALSE);
    gtk_tree_view_column_add_attribute(column, source_cell, "markup", 0);
    gtk_tree_view_column_add_attribute(column, source_cell, "yalign", 5);
    gtk_tree_view_column_pack_start(column, arrow_cell, FALSE);
    gtk_tree_view_column_add_attribute(column, arrow_cell, "text", 1);
    gtk_tree_view_column_pack_start(column, output_cell, TRUE);
    gtk_tree_view_column_add_attribute(column, output_cell, "markup", 2);
    gtk_tree_view_column_add_attribute(column, output_cell, "yalign", 5);
    gtk_tree_view_append_column(treeview, GTK_TREE_VIEW_COLUMN(column));
    gtk_tree_view_column_set_expand(column, TRUE);
    gtk_tree_view_column_set_max_width(column, 400);

    column = gtk_tree_view_column_new_with_attributes(
                                    _(""), edit_cell, "icon-name", 3, NULL);
    //gtk_tree_view_column_set_min_width(column, 24);
    gtk_tree_view_append_column(treeview, GTK_TREE_VIEW_COLUMN(column));

    column = gtk_tree_view_column_new_with_attributes(
                                    _(""), delete_cell, "icon-name", 4, NULL);
    //gtk_tree_view_column_set_min_width(column, 24);
    gtk_tree_view_append_column(treeview, GTK_TREE_VIEW_COLUMN(column));

    g_signal_connect(selection, "changed", audio_list_selection_changed_cb, ud);
    g_signal_connect(edit_cell, "clicked", audio_edit_clicked_cb, ud);
    g_signal_connect(delete_cell, "clicked", audio_remove_clicked_cb, ud);

    g_debug("Done\n");
}