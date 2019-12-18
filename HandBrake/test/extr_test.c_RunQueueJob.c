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
typedef  int /*<<< orphan*/  hb_handle_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 int /*<<< orphan*/  EventLoop (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hb_add_json (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hb_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 char* hb_value_get_json (int /*<<< orphan*/ *) ; 
 int job_running ; 
 int /*<<< orphan*/  stderr ; 

int RunQueueJob(hb_handle_t *h, hb_dict_t *job_dict)
{
    if (job_dict == NULL)
    {
        return -1;
    }

    char * json_job;
    json_job = hb_value_get_json(job_dict);
    hb_value_free(&job_dict);
    if (json_job == NULL)
    {
        fprintf(stderr, "Error in setting up job! Aborting.\n");
        return -1;
    }

    hb_add_json(h, json_job);
    free(json_job);
    job_running = 1;
    hb_start( h );

    EventLoop(h, NULL);

    return 0;
}