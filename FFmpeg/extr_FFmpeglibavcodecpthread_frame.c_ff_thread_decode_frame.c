#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int thread_count; scalar_t__ codec_id; TYPE_1__* internal; } ;
struct TYPE_23__ {int /*<<< orphan*/  pkt_dts; } ;
struct TYPE_22__ {int size; } ;
struct TYPE_21__ {int next_finished; size_t next_decoding; TYPE_3__* threads; scalar_t__ delaying; } ;
struct TYPE_19__ {int /*<<< orphan*/  dts; } ;
struct TYPE_20__ {int got_frame; int result; int /*<<< orphan*/  avctx; TYPE_2__ avpkt; int /*<<< orphan*/  frame; int /*<<< orphan*/  progress_mutex; int /*<<< orphan*/  output_cond; int /*<<< orphan*/  state; } ;
struct TYPE_18__ {TYPE_4__* thread_ctx; } ;
typedef  TYPE_3__ PerThreadContext ;
typedef  TYPE_4__ FrameThreadContext ;
typedef  TYPE_5__ AVPacket ;
typedef  TYPE_6__ AVFrame ;
typedef  TYPE_7__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_FFV1 ; 
 scalar_t__ STATE_INPUT_READY ; 
 int /*<<< orphan*/  async_lock (TYPE_4__*) ; 
 int /*<<< orphan*/  async_unlock (TYPE_4__*) ; 
 scalar_t__ atomic_load (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_load_explicit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_move_ref (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_order_relaxed ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int submit_packet (TYPE_3__*,TYPE_7__*,TYPE_5__*) ; 
 int /*<<< orphan*/  update_context_from_thread (TYPE_7__*,int /*<<< orphan*/ ,int) ; 

int ff_thread_decode_frame(AVCodecContext *avctx,
                           AVFrame *picture, int *got_picture_ptr,
                           AVPacket *avpkt)
{
    FrameThreadContext *fctx = avctx->internal->thread_ctx;
    int finished = fctx->next_finished;
    PerThreadContext *p;
    int err;

    /* release the async lock, permitting blocked hwaccel threads to
     * go forward while we are in this function */
    async_unlock(fctx);

    /*
     * Submit a packet to the next decoding thread.
     */

    p = &fctx->threads[fctx->next_decoding];
    err = submit_packet(p, avctx, avpkt);
    if (err)
        goto finish;

    /*
     * If we're still receiving the initial packets, don't return a frame.
     */

    if (fctx->next_decoding > (avctx->thread_count-1-(avctx->codec_id == AV_CODEC_ID_FFV1)))
        fctx->delaying = 0;

    if (fctx->delaying) {
        *got_picture_ptr=0;
        if (avpkt->size) {
            err = avpkt->size;
            goto finish;
        }
    }

    /*
     * Return the next available frame from the oldest thread.
     * If we're at the end of the stream, then we have to skip threads that
     * didn't output a frame/error, because we don't want to accidentally signal
     * EOF (avpkt->size == 0 && *got_picture_ptr == 0 && err >= 0).
     */

    do {
        p = &fctx->threads[finished++];

        if (atomic_load(&p->state) != STATE_INPUT_READY) {
            pthread_mutex_lock(&p->progress_mutex);
            while (atomic_load_explicit(&p->state, memory_order_relaxed) != STATE_INPUT_READY)
                pthread_cond_wait(&p->output_cond, &p->progress_mutex);
            pthread_mutex_unlock(&p->progress_mutex);
        }

        av_frame_move_ref(picture, p->frame);
        *got_picture_ptr = p->got_frame;
        picture->pkt_dts = p->avpkt.dts;
        err = p->result;

        /*
         * A later call with avkpt->size == 0 may loop over all threads,
         * including this one, searching for a frame/error to return before being
         * stopped by the "finished != fctx->next_finished" condition.
         * Make sure we don't mistakenly return the same frame/error again.
         */
        p->got_frame = 0;
        p->result = 0;

        if (finished >= avctx->thread_count) finished = 0;
    } while (!avpkt->size && !*got_picture_ptr && err >= 0 && finished != fctx->next_finished);

    update_context_from_thread(avctx, p->avctx, 1);

    if (fctx->next_decoding >= avctx->thread_count) fctx->next_decoding = 0;

    fctx->next_finished = finished;

    /* return the size of the consumed packet if no error occurred */
    if (err >= 0)
        err = avpkt->size;
finish:
    async_lock(fctx);
    return err;
}