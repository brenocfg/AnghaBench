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
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkListStore ;
typedef  int /*<<< orphan*/  GtkComboBox ;

/* Variables and functions */
 int /*<<< orphan*/ * GTK_LIST_STORE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ *) ; 
 scalar_t__ find_combo_item_by_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_combo_box_get_model (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static void
grey_combo_box_item(GtkComboBox *combo, gint value, gboolean grey)
{
    GtkListStore *store;
    GtkTreeIter iter;

    store = GTK_LIST_STORE(gtk_combo_box_get_model (combo));
    if (find_combo_item_by_int(GTK_TREE_MODEL(store), value, &iter))
    {
        gtk_list_store_set(store, &iter,
                           1, !grey,
                           -1);
    }
}