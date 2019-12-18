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
struct TYPE_3__ {int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  gint ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GtkTreeView ;
typedef  int /*<<< orphan*/  GtkTreeStore ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GTK_TREE_STORE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GTK_TREE_VIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ghb_find_lang_row (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ gtk_tree_model_get_iter_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_tree_model_iter_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_insert_before (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_model (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
audio_def_selected_lang_list_clear(signal_user_data_t *ud)
{
    GtkTreeView  * tv;
    GtkTreeModel * selected_tm;
    GtkTreeStore * avail_ts;
    GtkTreeIter    iter;

    tv          = GTK_TREE_VIEW(GHB_WIDGET(ud->builder, "audio_avail_lang"));
    avail_ts    = GTK_TREE_STORE(gtk_tree_view_get_model(tv));
    tv          = GTK_TREE_VIEW(GHB_WIDGET(ud->builder, "audio_selected_lang"));
    selected_tm = gtk_tree_view_get_model(tv);
    if (gtk_tree_model_get_iter_first(selected_tm, &iter))
    {
        do
        {
            gchar       * lang;
            gint          index;
            GtkTreeIter   pos, sibling;

            gtk_tree_model_get(selected_tm, &iter, 0, &lang, 1, &index, -1);
            if (ghb_find_lang_row(GTK_TREE_MODEL(avail_ts), &sibling, index))
            {
                gtk_tree_store_insert_before(avail_ts, &pos, NULL, &sibling);
            }
            else
            {
                gtk_tree_store_append(avail_ts, &pos, NULL);
            }
            gtk_tree_store_set(avail_ts, &pos, 0, lang, 1, index, -1);
            g_free(lang);
        } while (gtk_tree_model_iter_next(selected_tm, &iter));
    }
    gtk_tree_store_clear(GTK_TREE_STORE(selected_tm));
}