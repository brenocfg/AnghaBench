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
typedef  scalar_t__ gint ;
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkTreeView ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GTK_TREE_STORE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GTK_TREE_VIEW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_subtitle_list_ui (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ghb_array_len (int /*<<< orphan*/ *) ; 
 scalar_t__ ghb_dict_get_bool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ghb_get_job_subtitle_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_get_job_subtitle_search (int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_tree_model_iter_n_children (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_model_iter_nth_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  gtk_tree_store_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_model (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  subtitle_refresh_list_row_ui (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
subtitle_refresh_list_ui_from_settings(signal_user_data_t *ud, GhbValue *settings)
{
    GtkTreeView  *tv;
    GtkTreeModel *tm;
    GtkTreeIter   ti;
    GhbValue *subtitle_list, *subtitle_search;
    GhbValue *subsettings;
    gint ii, count, tm_count;
    gboolean search;

    tv = GTK_TREE_VIEW(GHB_WIDGET(ud->builder, "subtitle_list_view"));
    tm = gtk_tree_view_get_model(tv);

    tm_count = gtk_tree_model_iter_n_children(tm, NULL);

    subtitle_list = ghb_get_job_subtitle_list(settings);
    subtitle_search = ghb_get_job_subtitle_search(settings);
    search = ghb_dict_get_bool(subtitle_search, "Enable");
    count = ghb_array_len(subtitle_list);
    if (count + search != tm_count)
    {
        clear_subtitle_list_ui(ud->builder);
        for (ii = 0; ii < count + search; ii++)
        {
            gtk_tree_store_append(GTK_TREE_STORE(tm), &ti, NULL);
        }
    }
    // Enable or Disabel FAS button
    GtkWidget *w = GHB_WIDGET(ud->builder, "subtitle_add_fas");
    gtk_widget_set_sensitive(w, !search);
    if (search)
    {

        gtk_tree_model_iter_nth_child(tm, &ti, NULL, 0);
        subtitle_refresh_list_row_ui(tm, &ti, ud->settings, subtitle_search);
    }
    for (ii = 0; ii < count; ii++)
    {
        gtk_tree_model_iter_nth_child(tm, &ti, NULL, ii + search);
        subsettings = ghb_array_get(subtitle_list, ii);
        subtitle_refresh_list_row_ui(tm, &ti, ud->settings, subsettings);
    }
}