#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sync ;
typedef  int /*<<< orphan*/  out_frame ;
struct TYPE_9__ {int /*<<< orphan*/  frame; struct TYPE_9__* next; } ;
typedef  TYPE_2__ mfxSyncPoint ;
struct TYPE_8__ {int /*<<< orphan*/  mids_buf; int /*<<< orphan*/  hw_frames_ctx; } ;
struct TYPE_10__ {int /*<<< orphan*/  pool; TYPE_1__ frames_ctx; int /*<<< orphan*/  internal_qs; int /*<<< orphan*/ * async_fifo; TYPE_2__* work_frames; scalar_t__ session; } ;
typedef  TYPE_2__ QSVFrame ;
typedef  TYPE_4__ QSVContext ;

/* Variables and functions */
 int /*<<< orphan*/  MFXVideoDECODE_Close (scalar_t__) ; 
 int /*<<< orphan*/  av_buffer_pool_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_fifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_fifo_generic_read (int /*<<< orphan*/ *,TYPE_2__**,int,int /*<<< orphan*/ *) ; 
 scalar_t__ av_fifo_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 
 int /*<<< orphan*/  ff_qsv_close_internal_session (int /*<<< orphan*/ *) ; 

int ff_qsv_decode_close(QSVContext *q)
{
    QSVFrame *cur = q->work_frames;

    if (q->session)
        MFXVideoDECODE_Close(q->session);

    while (q->async_fifo && av_fifo_size(q->async_fifo)) {
        QSVFrame *out_frame;
        mfxSyncPoint *sync;

        av_fifo_generic_read(q->async_fifo, &out_frame, sizeof(out_frame), NULL);
        av_fifo_generic_read(q->async_fifo, &sync,      sizeof(sync),      NULL);

        av_freep(&sync);
    }

    while (cur) {
        q->work_frames = cur->next;
        av_frame_free(&cur->frame);
        av_freep(&cur);
        cur = q->work_frames;
    }

    av_fifo_free(q->async_fifo);
    q->async_fifo = NULL;

    ff_qsv_close_internal_session(&q->internal_qs);

    av_buffer_unref(&q->frames_ctx.hw_frames_ctx);
    av_buffer_unref(&q->frames_ctx.mids_buf);
    av_buffer_pool_uninit(&q->pool);

    return 0;
}