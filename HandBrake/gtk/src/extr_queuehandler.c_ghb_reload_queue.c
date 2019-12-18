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
struct TYPE_7__ {int /*<<< orphan*/ * queue; int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  scalar_t__ gint ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GHB_QUEUE_CANCELED ; 
 scalar_t__ GHB_QUEUE_DONE ; 
 int /*<<< orphan*/  GHB_QUEUE_PENDING ; 
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GTK_TOGGLE_TOOL_BUTTON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  add_to_queue_list (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ghb_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_array_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ghb_dict_get_value (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_dict_set_int (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ghb_find_pid_file () ; 
 int /*<<< orphan*/ * ghb_load_old_queue (scalar_t__) ; 
 int /*<<< orphan*/  ghb_queue_buttons_grey (TYPE_1__*) ; 
 int /*<<< orphan*/  ghb_queue_selection_init (TYPE_1__*) ; 
 int /*<<< orphan*/  ghb_remove_old_queue_file (scalar_t__) ; 
 int /*<<< orphan*/  ghb_save_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_update_pending (TYPE_1__*) ; 
 int /*<<< orphan*/  ghb_value_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ghb_write_pid_file () ; 
 int /*<<< orphan*/  gtk_toggle_tool_button_set_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

gboolean
ghb_reload_queue(signal_user_data_t *ud)
{
    GhbValue *queue;
    gint count, ii;
    gint pid;
    gint status;
    GhbValue *queueDict, *uiDict;

    g_debug("ghb_reload_queue");

find_pid:
    pid = ghb_find_pid_file();
    if (pid < 0)
        goto done;

    queue = ghb_load_old_queue(pid);
    ghb_remove_old_queue_file(pid);

    // Look for unfinished entries
    count = ghb_array_len(queue);
    for (ii = count-1; ii >= 0; ii--)
    {
        queueDict = ghb_array_get(queue, ii);
        uiDict = ghb_dict_get(queueDict, "uiSettings");
        if (uiDict == NULL ||
            ghb_dict_get_value(uiDict, "job_status") == NULL)
        {
            ghb_array_remove(queue, ii);
            continue;
        }
        status = ghb_dict_get_int(uiDict, "job_status");
        if (status == GHB_QUEUE_DONE || status == GHB_QUEUE_CANCELED)
        {
            ghb_array_remove(queue, ii);
            continue;
        }
    }
    count = ghb_array_len(queue);
    if (count == 0)
    {
        ghb_value_free(&queue);
        goto find_pid;
    }
    else
    {
        GtkWidget *widget = GHB_WIDGET(ud->builder, "show_queue");
        gtk_toggle_tool_button_set_active(GTK_TOGGLE_TOOL_BUTTON(widget), TRUE);
        ud->queue = queue;
        for (ii = 0; ii < count; ii++)
        {
            queueDict = ghb_array_get(queue, ii);
            uiDict = ghb_dict_get(queueDict, "uiSettings");
            ghb_dict_set_int(uiDict, "job_unique_id", 0);
            ghb_dict_set_int(uiDict, "job_status", GHB_QUEUE_PENDING);
            add_to_queue_list(ud, queueDict);
        }
        ghb_queue_buttons_grey(ud);
        ghb_save_queue(ud->queue);
        ghb_update_pending(ud);
        ghb_queue_selection_init(ud);
    }

done:
    ghb_write_pid_file();

    return FALSE;
}