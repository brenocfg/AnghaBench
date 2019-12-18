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
struct TYPE_4__ {int /*<<< orphan*/  settings; int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  scalar_t__ gint ;
typedef  int /*<<< orphan*/  GtkTreeView ;
typedef  int /*<<< orphan*/  GtkTreeSelection ;
typedef  int /*<<< orphan*/  GtkTreePath ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * GTK_TREE_VIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audio_refresh_list_row_ui (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ ghb_array_len (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ghb_get_job_audio_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_tree_model_get_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_path_free (int /*<<< orphan*/ *) ; 
 scalar_t__* gtk_tree_path_get_indices (int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_tree_selection_get_selected (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_selection (int /*<<< orphan*/ *) ; 

void
ghb_audio_list_refresh_selected(signal_user_data_t *ud)
{
    GtkTreeView *tv;
    GtkTreePath *tp;
    GtkTreeSelection *ts;
    GtkTreeModel *tm;
    GtkTreeIter ti;
    gint *indices;
    gint row;
    GhbValue *asettings = NULL;
    const GhbValue *audio_list;

    g_debug("ghb_audio_list_refresh_selected ()");
    tv = GTK_TREE_VIEW(GHB_WIDGET(ud->builder, "audio_list_view"));
    ts = gtk_tree_view_get_selection (tv);
    if (gtk_tree_selection_get_selected(ts, &tm, &ti))
    {
        // Get the row number
        tp = gtk_tree_model_get_path (tm, &ti);
        indices = gtk_tree_path_get_indices (tp);
        row = indices[0];
        gtk_tree_path_free(tp);
        if (row < 0) return;

        audio_list = ghb_get_job_audio_list(ud->settings);
        if (row >= ghb_array_len(audio_list))
            return;

        asettings = ghb_array_get(audio_list, row);
        audio_refresh_list_row_ui(tm, &ti, ud, asettings);
    }
}