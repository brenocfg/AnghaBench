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
typedef  scalar_t__ gdouble ;
typedef  int gboolean ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkListStore ;
typedef  int /*<<< orphan*/  GtkComboBox ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/ * GTK_LIST_STORE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ *) ; 
 int TRUE ; 
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/  gtk_combo_box_get_model (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,scalar_t__*,int) ; 
 scalar_t__ gtk_tree_model_get_iter_first (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_model_iter_next (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
ghb_audio_bitrate_opts_filter(
    GtkComboBox *combo,
    gint first_rate,
    gint last_rate)
{
    GtkTreeIter iter;
    GtkListStore *store;
    gdouble ivalue;
    gboolean done = FALSE;

    g_debug("audio_bitrate_opts_filter ()\n");
    store = GTK_LIST_STORE(gtk_combo_box_get_model (combo));
    if (gtk_tree_model_get_iter_first (GTK_TREE_MODEL(store), &iter))
    {
        do
        {
            gtk_tree_model_get(GTK_TREE_MODEL(store), &iter, 3, &ivalue, -1);
            if ((int)ivalue < first_rate || (int)ivalue > last_rate)
            {
                gtk_list_store_set(store, &iter, 1, FALSE, -1);
            }
            else
            {
                gtk_list_store_set(store, &iter, 1, TRUE, -1);
            }
            done = !gtk_tree_model_iter_next (GTK_TREE_MODEL(store), &iter);
        } while (!done);
    }
}