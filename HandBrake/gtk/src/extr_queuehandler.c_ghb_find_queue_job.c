#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ gint ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ghb_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 

gint
ghb_find_queue_job(GhbValue *queue, gint unique_id, GhbValue **job)
{
    GhbValue *queueDict, *uiDict;
    gint ii, count;
    gint job_unique_id;

    if (job != NULL)
    {
        *job = NULL;
    }
    if (unique_id == 0)  // Invalid Id
        return -1;

    count = ghb_array_len(queue);
    for (ii = 0; ii < count; ii++)
    {
        queueDict = ghb_array_get(queue, ii);
        uiDict = ghb_dict_get(queueDict, "uiSettings");
        job_unique_id = ghb_dict_get_int(uiDict, "job_unique_id");
        if (job_unique_id == unique_id)
        {
            if (job != NULL)
            {
                *job = queueDict;
            }
            return ii;
        }
    }
    return -1;
}