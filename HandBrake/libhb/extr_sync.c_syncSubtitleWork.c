#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_10__* stream; TYPE_9__* common; } ;
typedef  TYPE_3__ hb_work_private_t ;
struct TYPE_17__ {int* done; TYPE_3__* private_data; } ;
typedef  TYPE_4__ hb_work_object_t ;
struct TYPE_14__ {int flags; } ;
struct TYPE_18__ {TYPE_1__ s; } ;
typedef  TYPE_5__ hb_buffer_t ;
struct TYPE_19__ {TYPE_2__* job; } ;
struct TYPE_15__ {scalar_t__ indepth_scan; } ;
struct TYPE_13__ {int flush; int /*<<< orphan*/  common; scalar_t__ done; int /*<<< orphan*/  in_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  FlushBuffer (int /*<<< orphan*/ ) ; 
 int HB_BUF_FLAG_EOF ; 
 int HB_WORK_DONE ; 
 int HB_WORK_OK ; 
 int /*<<< orphan*/  QueueBuffer (TYPE_10__*,TYPE_5__*) ; 
 int /*<<< orphan*/  Synchronize (TYPE_10__*) ; 
 int /*<<< orphan*/  flushStreamsLock (TYPE_9__*) ; 
 int /*<<< orphan*/  hb_buffer_eof_init () ; 
 int /*<<< orphan*/  hb_list_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int syncSubtitleWork( hb_work_object_t * w, hb_buffer_t ** buf_in,
                             hb_buffer_t ** buf_out )
{
    hb_work_private_t * pv = w->private_data;
    hb_buffer_t * in = *buf_in;

    if (pv->stream->done)
    {
        FlushBuffer(pv->stream->common);
        return HB_WORK_DONE;
    }
    if (in->s.flags & HB_BUF_FLAG_EOF)
    {
        pv->stream->flush = 1;
        // sanitizeSubtitle requires EOF buffer to recognize that
        // it needs to flush all subtitles.
        hb_list_add(pv->stream->in_queue, hb_buffer_eof_init());
        flushStreamsLock(pv->common);
        if (pv->common->job->indepth_scan)
        {
            // When doing subtitle indepth scan, the pipeline ends at sync.
            // Terminate job when EOF reached.
            *w->done = 1;
        }
        return HB_WORK_DONE;
    }

    *buf_in = NULL;
    QueueBuffer(pv->stream, in);
    Synchronize(pv->stream);

    if (pv->stream->done)
    {
        FlushBuffer(pv->stream->common);
        return HB_WORK_DONE;
    }
    return HB_WORK_OK;
}