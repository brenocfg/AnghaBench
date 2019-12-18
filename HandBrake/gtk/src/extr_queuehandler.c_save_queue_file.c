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
struct TYPE_3__ {int /*<<< orphan*/  builder; int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  GtkWindow ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_QUEUE_PENDING ; 
 int /*<<< orphan*/  GHB_STOCK_CANCEL ; 
 int /*<<< orphan*/  GHB_STOCK_SAVE ; 
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GTK_DIALOG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_FILE_CHOOSER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_FILE_CHOOSER_ACTION_SAVE ; 
 scalar_t__ GTK_RESPONSE_ACCEPT ; 
 int /*<<< orphan*/  GTK_RESPONSE_CANCEL ; 
 int /*<<< orphan*/ * GTK_WINDOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ ,int) ; 
 int ghb_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_dict_set_int (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ghb_value_dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_value_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ghb_write_settings_file (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_dialog_run (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_file_chooser_dialog_new (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 char* gtk_file_chooser_get_filename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_file_chooser_set_current_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_widget_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
save_queue_file(signal_user_data_t *ud)
{
    int ii, count;
    GhbValue *queue = ghb_value_dup(ud->queue);

    count = ghb_array_len(queue);
    for (ii = 0; ii < count; ii++)
    {
        GhbValue *queueDict, *uiDict;

        queueDict = ghb_array_get(ud->queue, ii);
        uiDict = ghb_dict_get(queueDict, "uiSettings");
        if (uiDict == NULL)
            continue;
        ghb_dict_set_int(uiDict, "job_status", GHB_QUEUE_PENDING);
    }

    GtkWidget *dialog;
    GtkWindow *hb_window;

    hb_window = GTK_WINDOW(GHB_WIDGET(ud->builder, "hb_window"));
    dialog = gtk_file_chooser_dialog_new("Queue Destination",
                      hb_window,
                      GTK_FILE_CHOOSER_ACTION_SAVE,
                      GHB_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                      GHB_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
                      NULL);
    gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), "queue.json");
    if (gtk_dialog_run(GTK_DIALOG (dialog)) != GTK_RESPONSE_ACCEPT)
    {
        ghb_value_free(&queue);
        gtk_widget_destroy(dialog);
        return;
    }

    char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (dialog));
    gtk_widget_destroy(dialog);

    ghb_write_settings_file(filename, queue);
    g_free (filename);
    ghb_value_free(&queue);
}