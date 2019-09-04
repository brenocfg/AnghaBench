#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int thread_count; TYPE_2__* codec; TYPE_1__* internal; } ;
struct TYPE_12__ {int delaying; TYPE_3__* threads; TYPE_3__* prev_thread; scalar_t__ next_finished; scalar_t__ next_decoding; } ;
struct TYPE_11__ {int /*<<< orphan*/  avctx; scalar_t__ result; int /*<<< orphan*/  frame; scalar_t__ got_frame; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* flush ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {TYPE_4__* thread_ctx; } ;
typedef  TYPE_3__ PerThreadContext ;
typedef  TYPE_4__ FrameThreadContext ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_frame_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  park_frame_worker_threads (TYPE_4__*,int) ; 
 int /*<<< orphan*/  release_delayed_buffers (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_context_from_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ff_thread_flush(AVCodecContext *avctx)
{
    int i;
    FrameThreadContext *fctx = avctx->internal->thread_ctx;

    if (!fctx) return;

    park_frame_worker_threads(fctx, avctx->thread_count);
    if (fctx->prev_thread) {
        if (fctx->prev_thread != &fctx->threads[0])
            update_context_from_thread(fctx->threads[0].avctx, fctx->prev_thread->avctx, 0);
    }

    fctx->next_decoding = fctx->next_finished = 0;
    fctx->delaying = 1;
    fctx->prev_thread = NULL;
    for (i = 0; i < avctx->thread_count; i++) {
        PerThreadContext *p = &fctx->threads[i];
        // Make sure decode flush calls with size=0 won't return old frames
        p->got_frame = 0;
        av_frame_unref(p->frame);
        p->result = 0;

        release_delayed_buffers(p);

        if (avctx->codec->flush)
            avctx->codec->flush(p->avctx);
    }
}