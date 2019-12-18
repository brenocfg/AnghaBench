#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  settings; int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkTreeView ;
typedef  int /*<<< orphan*/  GtkTreeSelection ;
typedef  int /*<<< orphan*/  GtkTreePath ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  scalar_t__ GtkResponseType ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GTK_DIALOG (int /*<<< orphan*/ *) ; 
 scalar_t__ GTK_RESPONSE_OK ; 
 int /*<<< orphan*/  ghb_dict_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_get_job_settings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_get_job_subtitle_settings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_update_summary_info (TYPE_1__*) ; 
 int /*<<< orphan*/ * ghb_value_dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_value_free (int /*<<< orphan*/ **) ; 
 scalar_t__ gtk_dialog_run (int /*<<< orphan*/ ) ; 
 scalar_t__ gtk_tree_model_get_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int gtk_tree_path_get_depth (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_selection_select_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_model (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_selection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_hide (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * subtitle_get_selected_settings (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  subtitle_refresh_list_ui (TYPE_1__*) ; 
 int /*<<< orphan*/  subtitle_update_dialog_widgets (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
subtitle_edit(GtkTreeView *tv, GtkTreePath *tp, signal_user_data_t *ud)
{
    GtkTreeModel *tm;
    GtkTreeSelection *ts;
    GtkTreeIter ti;

    ts = gtk_tree_view_get_selection(tv);
    tm = gtk_tree_view_get_model(tv);
    if (gtk_tree_path_get_depth(tp) > 1) return;
    if (gtk_tree_model_get_iter(tm, &ti, tp))
    {
        GhbValue *subsettings, *backup;

        gtk_tree_selection_select_iter(ts, &ti);

        // Back up settings in case we need to revert.
        backup = ghb_value_dup(ghb_get_job_subtitle_settings(ud->settings));

        // Pop up the edit dialog
        GtkResponseType response;
        GtkWidget *dialog = GHB_WIDGET(ud->builder, "subtitle_dialog");
        response = gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_hide(dialog);
        if (response != GTK_RESPONSE_OK)
        {
            ghb_dict_set(ghb_get_job_settings(ud->settings),
                         "Subtitle", backup);
            subsettings = subtitle_get_selected_settings(ud, NULL);
            if (subsettings != NULL)
            {
                subtitle_update_dialog_widgets(ud, subsettings);
            }
            subtitle_refresh_list_ui(ud);
        }
        else
        {
            ghb_value_free(&backup);
        }
        ghb_update_summary_info(ud);
    }
}