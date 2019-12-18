#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {struct TYPE_14__* private_data; struct TYPE_14__* common; struct TYPE_14__* streams; int /*<<< orphan*/  mutex; int /*<<< orphan*/  list_work; int /*<<< orphan*/  (* close ) (TYPE_2__*) ;int /*<<< orphan*/ * thread; TYPE_1__* stream; int /*<<< orphan*/  est_frame_count; TYPE_5__* job; } ;
typedef  TYPE_2__ sync_delta_t ;
typedef  TYPE_2__ hb_work_private_t ;
typedef  TYPE_2__ hb_work_object_t ;
struct TYPE_15__ {scalar_t__ pass_id; int /*<<< orphan*/  h; } ;
typedef  TYPE_5__ hb_job_t ;
struct TYPE_16__ {int frame_count; } ;
typedef  TYPE_6__ hb_interjob_t ;
struct TYPE_13__ {int frame_count; int min_frame_duration; int max_frame_duration; int current_duration; int /*<<< orphan*/  scr_delay_queue; int /*<<< orphan*/  in_queue; int /*<<< orphan*/  delta_list; } ;

/* Variables and functions */
 scalar_t__ HB_PASS_ENCODE_1ST ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_6__* hb_interjob_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_list_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_list_empty (int /*<<< orphan*/ *) ; 
 TYPE_2__* hb_list_item (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_list_rem (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  hb_lock_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_log (char*,int,int,...) ; 
 int /*<<< orphan*/  hb_thread_close (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void syncVideoClose( hb_work_object_t * w )
{
    hb_work_private_t * pv   = w->private_data;
    hb_job_t          * job;

    if (pv == NULL)
    {
        return;
    }
    job = pv->common->job;

    hb_log("sync: got %d frames, %d expected",
           pv->stream->frame_count, pv->common->est_frame_count );
    if (pv->stream->min_frame_duration > 0 &&
        pv->stream->max_frame_duration > 0 &&
        pv->stream->current_duration > 0)
    {
        hb_log("sync: framerate min %.3f fps, max %.3f fps, avg %.3f fps",
               90000. / pv->stream->max_frame_duration,
               90000. / pv->stream->min_frame_duration,
               (pv->stream->frame_count * 90000.) /
                pv->stream->current_duration);
    }

    /* save data for second pass */
    if( job->pass_id == HB_PASS_ENCODE_1ST )
    {
        /* Preserve frame count for better accuracy in pass 2 */
        hb_interjob_t * interjob = hb_interjob_get( job->h );
        interjob->frame_count = pv->stream->frame_count;
    }
    sync_delta_t * delta;
    while ((delta = hb_list_item(pv->stream->delta_list, 0)) != NULL)
    {
        hb_list_rem(pv->stream->delta_list, delta);
        free(delta);
    }
    hb_list_close(&pv->stream->delta_list);
    hb_list_empty(&pv->stream->in_queue);
    hb_list_empty(&pv->stream->scr_delay_queue);

    // Close work threads
    hb_work_object_t * work;
    while ((work = hb_list_item(pv->common->list_work, 0)))
    {
        hb_list_rem(pv->common->list_work, work);
        if (work->thread != NULL)
        {
            hb_thread_close(&work->thread);
        }
        if (work->close) work->close(work);
        free(work);
    }
    hb_list_close(&pv->common->list_work);

    hb_lock_close(&pv->common->mutex);
    free(pv->common->streams);
    free(pv->common);
    free(pv);
    w->private_data = NULL;
}