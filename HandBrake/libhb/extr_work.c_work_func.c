#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_12__ {int* die; TYPE_2__** current_job; int /*<<< orphan*/ * error; int /*<<< orphan*/ * jobs; } ;
typedef  TYPE_1__ hb_work_t ;
typedef  int /*<<< orphan*/  hb_list_t ;
struct TYPE_13__ {int* die; int /*<<< orphan*/ * done_error; int /*<<< orphan*/ * h; int /*<<< orphan*/  sequence_id; int /*<<< orphan*/ * json; } ;
typedef  TYPE_2__ hb_job_t ;
typedef  int /*<<< orphan*/  hb_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  HB_ERROR_INIT ; 
 int /*<<< orphan*/  InitWorkState (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  SetWorkStateInfo (TYPE_2__*) ; 
 int asctime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_job (TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  hb_deep_log (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_force_rescan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_job_close (TYPE_2__**) ; 
 int /*<<< orphan*/  hb_job_setup_passes (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_json_job_scan (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* hb_json_to_job (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_list_close (int /*<<< orphan*/ **) ; 
 int hb_list_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_list_init () ; 
 TYPE_2__* hb_list_item (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hb_list_rem (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  hb_log (char*,int) ; 
 int /*<<< orphan*/  localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void work_func( void * _work )
{
    hb_work_t  * work = _work;
    hb_job_t   * job;

    time_t t = time(NULL);
    hb_log("Starting work at: %s", asctime(localtime(&t)));
    hb_log( "%d job(s) to process", hb_list_count( work->jobs ) );

    while( !*work->die && ( job = hb_list_item( work->jobs, 0 ) ) )
    {
        hb_handle_t * h = job->h;

        hb_list_rem( work->jobs, job );
        hb_list_t * passes = hb_list_init();

        // JSON jobs get special treatment.  We want to perform the title
        // scan for the JSON job automatically.  This requires that we delay
        // filling the job struct till we have performed the title scan
        // because the default values for the job come from the title.
        if (job->json != NULL)
        {
            hb_deep_log(1, "json job:\n%s", job->json);

            // Initialize state sequence_id
            InitWorkState(job, 0, 0);
            // Perform title scan for json job
            hb_json_job_scan(job->h, job->json);

            // Expand json string to full job struct
            hb_job_t *new_job = hb_json_to_job(job->h, job->json);
            if (new_job == NULL)
            {
                hb_job_close(&job);
                hb_list_close(&passes);
                *work->error = HB_ERROR_INIT;
                *work->die = 1;
                break;
            }
            new_job->h = job->h;
            new_job->sequence_id = job->sequence_id;
            hb_job_close(&job);
            job = new_job;
        }
        hb_job_setup_passes(job->h, job, passes);
        hb_job_close(&job);

        int pass_count, pass;
        pass_count = hb_list_count(passes);
        for (pass = 0; pass < pass_count && !*work->die; pass++)
        {
            job = hb_list_item(passes, pass);
            job->die = work->die;
            job->done_error = work->error;
            *(work->current_job) = job;
            InitWorkState(job, pass + 1, pass_count);
            do_job( job );
        }
        SetWorkStateInfo(job);
        *(work->current_job) = NULL;

        // Clean job passes
        for (pass = 0; pass < pass_count; pass++)
        {
            job = hb_list_item(passes, pass);
            hb_job_close(&job);
        }
        hb_list_close(&passes);

        // Force rescan of next source processed by this hb_handle_t
        // TODO: Fix this ugly hack!
        hb_force_rescan(h);
    }

    t = time(NULL);
    hb_log("Finished work at: %s", asctime(localtime(&t)));
    free( work );
}