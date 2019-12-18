#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sync ;
typedef  int /*<<< orphan*/  pkt ;
struct TYPE_13__ {int /*<<< orphan*/  Payload; } ;
struct TYPE_14__ {TYPE_2__ enc_ctrl; int /*<<< orphan*/  frame; struct TYPE_14__* next; } ;
typedef  TYPE_3__ mfxSyncPoint ;
typedef  TYPE_3__ mfxBitstream ;
typedef  int /*<<< orphan*/  bs ;
struct TYPE_12__ {int /*<<< orphan*/  mids_buf; int /*<<< orphan*/  hw_frames_ctx; } ;
struct TYPE_15__ {TYPE_3__* extparam; int /*<<< orphan*/  opaque_alloc_buf; TYPE_3__* opaque_surfaces; int /*<<< orphan*/ * async_fifo; TYPE_3__* work_frames; TYPE_1__ frames_ctx; int /*<<< orphan*/  internal_qs; int /*<<< orphan*/ * session; } ;
typedef  TYPE_3__ QSVFrame ;
typedef  TYPE_6__ QSVEncContext ;
typedef  TYPE_3__* AVPacket ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  MFXVideoENCODE_Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_fifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_fifo_generic_read (int /*<<< orphan*/ *,TYPE_3__**,int,int /*<<< orphan*/ *) ; 
 scalar_t__ av_fifo_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (TYPE_3__**) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_3__**) ; 
 int /*<<< orphan*/  ff_qsv_close_internal_session (int /*<<< orphan*/ *) ; 

int ff_qsv_enc_close(AVCodecContext *avctx, QSVEncContext *q)
{
    QSVFrame *cur;

    if (q->session)
        MFXVideoENCODE_Close(q->session);

    q->session          = NULL;
    ff_qsv_close_internal_session(&q->internal_qs);

    av_buffer_unref(&q->frames_ctx.hw_frames_ctx);
    av_buffer_unref(&q->frames_ctx.mids_buf);

    cur = q->work_frames;
    while (cur) {
        q->work_frames = cur->next;
        av_frame_free(&cur->frame);
        av_free(cur->enc_ctrl.Payload);
        av_freep(&cur);
        cur = q->work_frames;
    }

    while (q->async_fifo && av_fifo_size(q->async_fifo)) {
        AVPacket pkt;
        mfxSyncPoint *sync;
        mfxBitstream *bs;

        av_fifo_generic_read(q->async_fifo, &pkt,  sizeof(pkt),  NULL);
        av_fifo_generic_read(q->async_fifo, &sync, sizeof(sync), NULL);
        av_fifo_generic_read(q->async_fifo, &bs,   sizeof(bs),   NULL);

        av_freep(&sync);
        av_freep(&bs);
        av_packet_unref(&pkt);
    }
    av_fifo_free(q->async_fifo);
    q->async_fifo = NULL;

    av_freep(&q->opaque_surfaces);
    av_buffer_unref(&q->opaque_alloc_buf);

    av_freep(&q->extparam);

    return 0;
}