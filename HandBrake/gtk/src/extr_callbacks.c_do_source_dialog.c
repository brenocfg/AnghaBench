#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  prefs; int /*<<< orphan*/  settings; int /*<<< orphan*/  builder; int /*<<< orphan*/  globals; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  scalar_t__ gint ;
typedef  int /*<<< orphan*/  gchar ;
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GTK_DIALOG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_FILE_CHOOSER (int /*<<< orphan*/ *) ; 
 scalar_t__ GTK_RESPONSE_NO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ghb_dict_get_int (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ghb_dict_get_string (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ghb_dict_set_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_do_scan (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_dvd_set_current (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ghb_pref_save (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gtk_dialog_run (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_file_chooser_get_filename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_file_chooser_select_filename (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  gtk_widget_hide (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  source_dialog_extra_widgets (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
do_source_dialog(gboolean single, signal_user_data_t *ud)
{
    GtkWidget *dialog;
    const gchar *sourcename;
    gint    response;

    g_debug("source_browse_clicked_cb ()");
    sourcename = ghb_dict_get_string(ud->globals, "scan_source");
    GtkWidget *widget;
    widget = GHB_WIDGET(ud->builder, "single_title_box");
    if (single)
        gtk_widget_show(widget);
    else
        gtk_widget_hide(widget);
    dialog = GHB_WIDGET(ud->builder, "source_dialog");
    source_dialog_extra_widgets(ud, dialog);

    gtk_widget_show(dialog);
    gtk_file_chooser_select_filename(GTK_FILE_CHOOSER(dialog), sourcename);

    response = gtk_dialog_run(GTK_DIALOG (dialog));
    gtk_widget_hide(dialog);
    if (response == GTK_RESPONSE_NO)
    {
        gchar *filename;

        filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
        if (filename != NULL)
        {
            gint title_id;

            if (single)
                title_id = ghb_dict_get_int(ud->settings, "single_title");
            else
                title_id = 0;
            // ghb_do_scan replaces "scan_source" key in dict, so we must
            // be finished with sourcename before calling ghb_do_scan
            // since the memory it references will be freed
            if (strcmp(sourcename, filename) != 0)
            {
                ghb_dict_set_string(ud->prefs, "default_source", filename);
                ghb_pref_save(ud->prefs, "default_source");
                ghb_dvd_set_current(filename, ud);
            }
            ghb_do_scan(ud, filename, title_id, TRUE);
            g_free(filename);
        }
    }
}