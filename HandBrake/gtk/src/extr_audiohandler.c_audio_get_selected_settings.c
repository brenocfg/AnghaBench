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
struct TYPE_3__ {int /*<<< orphan*/  settings; int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int gint ;
typedef  int /*<<< orphan*/  GtkTreeView ;
typedef  int /*<<< orphan*/  GtkTreeSelection ;
typedef  int /*<<< orphan*/  GtkTreePath ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * GTK_TREE_VIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/  const*,int) ; 
 int ghb_array_len (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ghb_get_job_audio_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_tree_model_get_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_path_free (int /*<<< orphan*/ *) ; 
 int* gtk_tree_path_get_indices (int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_tree_selection_get_selected (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_selection (int /*<<< orphan*/ *) ; 

__attribute__((used)) static GhbValue*
audio_get_selected_settings(signal_user_data_t *ud, int *index)
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

    tv = GTK_TREE_VIEW(GHB_WIDGET(ud->builder, "audio_list_view"));
    ts = gtk_tree_view_get_selection (tv);
    if (gtk_tree_selection_get_selected(ts, &tm, &ti))
    {
        // Get the row number
        tp = gtk_tree_model_get_path (tm, &ti);
        indices = gtk_tree_path_get_indices (tp);
        row = indices[0];
        gtk_tree_path_free(tp);
        // find audio settings
        if (row < 0) return NULL;

        audio_list = ghb_get_job_audio_list(ud->settings);
        if (row >= ghb_array_len(audio_list))
            return NULL;

        asettings = ghb_array_get(audio_list, row);
        if (index != NULL)
            *index = row;
    }
    return asettings;
}