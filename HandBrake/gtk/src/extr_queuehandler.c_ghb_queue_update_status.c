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
struct TYPE_5__ {int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int GHB_QUEUE_PENDING ; 
 scalar_t__ GHB_QUEUE_RUNNING ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ ,int) ; 
 int ghb_array_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_dict_set_int (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ghb_queue_progress_set_visible (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_queue_update_status_icon (TYPE_1__*,int) ; 

void
ghb_queue_update_status(signal_user_data_t *ud, int index, int status)
{
    int count = ghb_array_len(ud->queue);
    if (index < 0 || index >= count)
    {
        // invalid index
        return;
    }

    GhbValue * queueDict, * uiDict;
    queueDict = ghb_array_get(ud->queue, index);
    if (queueDict == NULL) // should never happen
    {
        return;
    }
    uiDict    = ghb_dict_get(queueDict, "uiSettings");
    if (uiDict == NULL) // should never happen
    {
        return;
    }

    if (ghb_dict_get_int(uiDict, "job_status") == GHB_QUEUE_RUNNING)
    {
        return; // Never change the status of currently running jobs
    }

    if (status == GHB_QUEUE_PENDING)
    {
        ghb_queue_progress_set_visible(ud, index, FALSE);
    }
    ghb_dict_set_int(uiDict, "job_status", status);
    ghb_queue_update_status_icon(ud, index);
}