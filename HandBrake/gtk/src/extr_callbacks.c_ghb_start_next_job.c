#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  globals; int /*<<< orphan*/  queue; int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  scalar_t__ gint ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GHB_QUEUE_PENDING ; 
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ghb_array_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_dict_set_bool (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_inhibit_suspend (TYPE_1__*) ; 
 int /*<<< orphan*/  ghb_notify_done (TYPE_1__*) ; 
 int /*<<< orphan*/  ghb_uninhibit_suspend (TYPE_1__*) ; 
 int /*<<< orphan*/  ghb_update_pending (TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_widget_hide (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  submit_job (TYPE_1__*,int /*<<< orphan*/ *) ; 

void
ghb_start_next_job(signal_user_data_t *ud)
{
    gint count, ii;
    GhbValue *queueDict, *uiDict;
    gint status;
    GtkWidget *progress;

    g_debug("start_next_job");
    progress = GHB_WIDGET(ud->builder, "progressbar");
    gtk_widget_show(progress);

    count = ghb_array_len(ud->queue);
    for (ii = 0; ii < count; ii++)
    {

        queueDict = ghb_array_get(ud->queue, ii);
        uiDict = ghb_dict_get(queueDict, "uiSettings");
        status = ghb_dict_get_int(uiDict, "job_status");
        if (status == GHB_QUEUE_PENDING)
        {
            ghb_inhibit_suspend(ud);
            submit_job(ud, queueDict);
            ghb_update_pending(ud);
            return;
        }
    }
    // Nothing pending
    ghb_uninhibit_suspend(ud);
    ghb_notify_done(ud);
    ghb_update_pending(ud);
    gtk_widget_hide(progress);
    ghb_dict_set_bool(ud->globals, "SkipDiskFreeCheck", FALSE);
}