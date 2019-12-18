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
struct TYPE_5__ {int /*<<< orphan*/ * extra_activity_buffer; int /*<<< orphan*/ * extra_activity_path; int /*<<< orphan*/ * queue_activity_buffer; int /*<<< orphan*/  builder; int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  scalar_t__ gint ;
typedef  int /*<<< orphan*/  GtkTextView ;
typedef  int /*<<< orphan*/  GtkTextBuffer ;
typedef  int /*<<< orphan*/  GtkListBoxRow ;
typedef  int /*<<< orphan*/  GtkListBox ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int GHB_QUEUE_PENDING ; 
 int GHB_QUEUE_RUNNING ; 
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * GTK_LIST_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GTK_TEXT_VIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ghb_array_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 char* ghb_dict_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_string_value (char const*) ; 
 int /*<<< orphan*/  ghb_ui_update (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_list_box_get_selected_row (int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_list_box_row_get_index (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_text_buffer_set_text (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_text_view_get_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_text_view_set_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_log (TYPE_1__*,char const*) ; 

void ghb_queue_select_log(signal_user_data_t * ud)
{
    GtkListBox    * lb;
    GtkListBoxRow * row;
    GtkTextBuffer * current;
    gint            index;
    GhbValue      * queueDict, *uiDict;

    lb              = GTK_LIST_BOX(GHB_WIDGET(ud->builder, "queue_list"));
    row             = gtk_list_box_get_selected_row(lb);
    if (row != NULL)
    {
        // There is a queue list row selected
        GtkTextView * tv;
        int           status;
        const char  * log_path;

        index = gtk_list_box_row_get_index(row);
        if (index < 0 || index >= ghb_array_len(ud->queue))
        { // Should never happen
            return;
        }
        queueDict = ghb_array_get(ud->queue, index);
        uiDict = ghb_dict_get(queueDict, "uiSettings");
        // Get the current buffer that is displayed in the queue log
        tv = GTK_TEXT_VIEW(GHB_WIDGET(ud->builder, "queue_activity_view"));
        current = gtk_text_view_get_buffer(tv);

        status = ghb_dict_get_int(uiDict, "job_status");
        log_path = ghb_dict_get_string(uiDict, "ActivityFilename");
        if (status != GHB_QUEUE_PENDING && log_path != NULL)
        {
            ghb_ui_update(ud, "queue_activity_location",
                          ghb_string_value(log_path));
        }
        else
        {
            ghb_ui_update(ud, "queue_activity_location", ghb_string_value(""));
        }
        if (status == GHB_QUEUE_RUNNING)
        {
            // Selected encode is running, enable display of log and
            // show the live buffer
            if (ud->queue_activity_buffer != current)
            {
                gtk_text_view_set_buffer(tv, ud->queue_activity_buffer);
            }
        }
        else
        {
            // Selected encode is pending/finished/canceled/failed
            // use non-live buffer (aka extra) to display log
            if (ud->extra_activity_buffer != current)
            {
                gtk_text_view_set_buffer(tv, ud->extra_activity_buffer);
            }
            log_path = ghb_dict_get_string(uiDict, "ActivityFilename");
            if (status != GHB_QUEUE_PENDING && log_path != NULL)
            {
                // enable display of log and read log into display buffer
                read_log(ud, log_path);
            }
            else
            {
                // No log file, encode is pending
                // disable display of log
                g_free(ud->extra_activity_path);
                ud->extra_activity_path = NULL;
                gtk_text_buffer_set_text(ud->extra_activity_buffer, "", 0);
            }
        }
    }
}