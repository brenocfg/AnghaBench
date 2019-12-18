#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * queue; int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  GtkWindow ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkFileFilter ;
typedef  int /*<<< orphan*/  GtkFileChooser ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_OBJECT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GHB_QUEUE_PENDING ; 
 int /*<<< orphan*/  GHB_STOCK_CANCEL ; 
 int /*<<< orphan*/  GHB_STOCK_OPEN ; 
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GTK_DIALOG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GTK_FILE_CHOOSER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_FILE_CHOOSER_ACTION_OPEN ; 
 int /*<<< orphan*/ * GTK_FILE_FILTER (int /*<<< orphan*/ ) ; 
 scalar_t__ GTK_RESPONSE_ACCEPT ; 
 int /*<<< orphan*/  GTK_RESPONSE_CANCEL ; 
 int /*<<< orphan*/ * GTK_WINDOW (int /*<<< orphan*/ ) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  add_to_queue_list (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  ghb_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ *,int) ; 
 int ghb_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_array_new () ; 
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_dict_set_int (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_queue_buttons_grey (TYPE_1__*) ; 
 int /*<<< orphan*/ * ghb_read_settings_file (char*) ; 
 int /*<<< orphan*/  ghb_save_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_value_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ghb_value_incref (int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_dialog_run (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_file_chooser_add_filter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_file_chooser_dialog_new (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 char* gtk_file_chooser_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_file_filter_add_pattern (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gtk_file_filter_set_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gtk_widget_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
open_queue_file(signal_user_data_t *ud)
{
    GtkWidget *dialog;
    GtkWindow *hb_window;

    hb_window = GTK_WINDOW(GHB_WIDGET(ud->builder, "hb_window"));
    dialog = gtk_file_chooser_dialog_new("Queue Destination",
                      hb_window,
                      GTK_FILE_CHOOSER_ACTION_OPEN,
                      GHB_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                      GHB_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                      NULL);

    // Add filters
    GtkFileFilter *filter;
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
    filter = GTK_FILE_FILTER(GHB_OBJECT(ud->builder, "QueueFilterAll"));
    gtk_file_filter_set_name(filter, _("All"));
    gtk_file_filter_add_pattern(filter, "*");
    gtk_file_chooser_add_filter(chooser, filter);
    filter = GTK_FILE_FILTER(GHB_OBJECT(ud->builder, "QueueFilterJSON"));
    gtk_file_filter_set_name(filter, "JSON");
    gtk_file_filter_add_pattern(filter, "*.JSON");
    gtk_file_filter_add_pattern(filter, "*.json");
    gtk_file_chooser_add_filter(chooser, filter);

    if (gtk_dialog_run(GTK_DIALOG (dialog)) != GTK_RESPONSE_ACCEPT)
    {
        gtk_widget_destroy(dialog);
        return;
    }

    GhbValue *queue;
    char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
    gtk_widget_destroy(dialog);

    queue = ghb_read_settings_file(filename);
    if (queue != NULL)
    {
        int ii, count;
        count = ghb_array_len(queue);
        for (ii = 0; ii < count; ii++)
        {
            GhbValue *queueDict, *uiDict;

            queueDict = ghb_array_get(queue, ii);
            uiDict = ghb_dict_get(queueDict, "uiSettings");
            ghb_value_incref(queueDict);
            ghb_dict_set_int(uiDict, "job_status", GHB_QUEUE_PENDING);
            ghb_dict_set_int(uiDict, "job_unique_id", 0);

            if (ud->queue == NULL)
                ud->queue = ghb_array_new();
            ghb_array_append(ud->queue, queueDict);
            add_to_queue_list(ud, queueDict);
        }
        ghb_queue_buttons_grey(ud);
        ghb_save_queue(ud->queue);
        ghb_value_free(&queue);
    }
    g_free (filename);
}