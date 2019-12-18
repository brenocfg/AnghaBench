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
typedef  int /*<<< orphan*/  GtkListStore ;
typedef  int /*<<< orphan*/  GtkComboBox ;
typedef  int /*<<< orphan*/  GtkCellRenderer ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_CELL_LAYOUT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GTK_CELL_RENDERER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_COMBO_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_TYPE_BOOLEAN ; 
 int /*<<< orphan*/  G_TYPE_DOUBLE ; 
 int /*<<< orphan*/  G_TYPE_STRING ; 
 int PANGO_ELLIPSIZE_END ; 
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/  g_object_set (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_cell_layout_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_cell_layout_pack_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_cell_layout_set_attributes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_cell_renderer_text_new () ; 
 int /*<<< orphan*/  gtk_combo_box_get_has_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_combo_box_set_entry_text_column (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_combo_box_set_model (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_list_store_new (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ghb_init_combo_box(GtkComboBox *combo)
{
    GtkListStore *store;
    GtkCellRenderer *cell;

    g_debug("ghb_init_combo_box()\n");
    // First modify the combobox model to allow greying out of options
    if (combo == NULL)
        return;
    // Store contains:
    // 1 - String to display
    // 2 - bool indicating whether the entry is selectable (grey or not)
    // 3 - String that is used for presets
    // 4 - Int value determined by backend
    store = gtk_list_store_new(4, G_TYPE_STRING, G_TYPE_BOOLEAN,
                               G_TYPE_STRING, G_TYPE_DOUBLE);
    gtk_combo_box_set_model(combo, GTK_TREE_MODEL(store));

    if (!gtk_combo_box_get_has_entry(combo))
    {
        gtk_cell_layout_clear(GTK_CELL_LAYOUT(combo));
        cell = GTK_CELL_RENDERER(gtk_cell_renderer_text_new());
        g_object_set(cell, "max-width-chars", 80, NULL);
        g_object_set(cell, "ellipsize", PANGO_ELLIPSIZE_END, NULL);
        gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(combo), cell, FALSE);
        gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(combo), cell,
            "markup", 0, "sensitive", 1, NULL);
    }
    else
    { // Combo box entry
        gtk_combo_box_set_entry_text_column(GTK_COMBO_BOX(combo), 0);
    }
}