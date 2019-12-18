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
struct TYPE_4__ {int /*<<< orphan*/  builder; int /*<<< orphan*/  settings; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  scalar_t__ gint ;
typedef  int /*<<< orphan*/  GtkTreeView ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GTK_TREE_STORE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GTK_TREE_VIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audio_refresh_list_row_ui (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ghb_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_clear_audio_list_ui (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ghb_get_job_audio_list (int /*<<< orphan*/ ) ; 
 scalar_t__ gtk_tree_model_iter_n_children (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_model_iter_nth_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  gtk_tree_store_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_model (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
audio_refresh_list_ui(signal_user_data_t *ud)
{
    GhbValue *audio_list;
    GhbValue *asettings;
    gint ii, count, tm_count;
    GtkTreeView *tv;
    GtkTreeModel *tm;
    GtkTreeIter ti;

    tv = GTK_TREE_VIEW(GHB_WIDGET(ud->builder, "audio_list_view"));
    tm = gtk_tree_view_get_model(tv);

    tm_count = gtk_tree_model_iter_n_children(tm, NULL);

    audio_list = ghb_get_job_audio_list(ud->settings);
    count = ghb_array_len(audio_list);
    if (count != tm_count)
    {
        ghb_clear_audio_list_ui(ud->builder);
        for (ii = 0; ii < count; ii++)
        {
            gtk_tree_store_append(GTK_TREE_STORE(tm), &ti, NULL);
        }
    }
    for (ii = 0; ii < count; ii++)
    {
        gtk_tree_model_iter_nth_child(tm, &ti, NULL, ii);
        asettings = ghb_array_get(audio_list, ii);
        audio_refresh_list_row_ui(tm, &ti, ud, asettings);
    }
}