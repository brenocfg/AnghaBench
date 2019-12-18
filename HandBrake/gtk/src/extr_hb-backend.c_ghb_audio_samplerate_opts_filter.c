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
typedef  double gdouble ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkListStore ;
typedef  int /*<<< orphan*/  GtkComboBox ;

/* Variables and functions */
 int /*<<< orphan*/ * GTK_LIST_STORE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gtk_combo_box_get_model (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,double*,int) ; 
 int /*<<< orphan*/  gtk_tree_model_get_iter_first (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_tree_model_iter_next (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_audio_samplerate_is_supported (double,int /*<<< orphan*/ ) ; 

void
ghb_audio_samplerate_opts_filter(GtkComboBox *combo, gint acodec)
{
    GtkTreeIter iter;
    GtkListStore *store;
    gdouble irate;

    store = GTK_LIST_STORE(gtk_combo_box_get_model(combo));
    if (!gtk_tree_model_get_iter_first( GTK_TREE_MODEL(store), &iter))
        return;

    do
    {
        gtk_tree_model_get(GTK_TREE_MODEL(store), &iter, 3, &irate, -1);
        // If irate == 0.0, the item is the "Same as Source" item,
        // so set to TRUE. Otherwise, ask libhb
        gtk_list_store_set(store, &iter, 1, irate == 0.0 ? TRUE :
                hb_audio_samplerate_is_supported(irate, acodec), -1);
    } while (gtk_tree_model_iter_next(GTK_TREE_MODEL(store), &iter));
}