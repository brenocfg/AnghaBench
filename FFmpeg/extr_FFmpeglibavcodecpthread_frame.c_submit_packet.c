#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int debug; scalar_t__ get_format; scalar_t__ get_buffer2; int /*<<< orphan*/  thread_safe_callbacks; TYPE_4__* codec; } ;
struct TYPE_18__ {int capabilities; } ;
struct TYPE_17__ {int /*<<< orphan*/  size; } ;
struct TYPE_16__ {int /*<<< orphan*/  next_decoding; TYPE_1__* prev_thread; } ;
struct TYPE_15__ {int /*<<< orphan*/  progress_mutex; int /*<<< orphan*/  progress_cond; int /*<<< orphan*/  state; int /*<<< orphan*/  available_formats; TYPE_5__* avctx; int /*<<< orphan*/  result_format; int /*<<< orphan*/  requested_flags; int /*<<< orphan*/  requested_frame; int /*<<< orphan*/  result; int /*<<< orphan*/  mutex; int /*<<< orphan*/  input_cond; int /*<<< orphan*/  avpkt; int /*<<< orphan*/  debug_threads; TYPE_2__* parent; } ;
typedef  TYPE_1__ PerThreadContext ;
typedef  TYPE_2__ FrameThreadContext ;
typedef  TYPE_3__ AVPacket ;
typedef  int /*<<< orphan*/  AVCodecContext ;
typedef  TYPE_4__ AVCodec ;

/* Variables and functions */
 int AV_CODEC_CAP_DELAY ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FF_DEBUG_THREADS ; 
#define  STATE_GET_BUFFER 129 
#define  STATE_GET_FORMAT 128 
 scalar_t__ STATE_INPUT_READY ; 
 scalar_t__ STATE_SETTING_UP ; 
 scalar_t__ STATE_SETUP_FINISHED ; 
 scalar_t__ atomic_load (int /*<<< orphan*/ *) ; 
 int atomic_load_explicit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  atomic_store_explicit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int av_packet_ref (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 scalar_t__ avcodec_default_get_buffer2 ; 
 scalar_t__ avcodec_default_get_format ; 
 int /*<<< orphan*/  ff_get_buffer (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_get_format (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_order_acquire ; 
 int /*<<< orphan*/  memory_order_relaxed ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_delayed_buffers (TYPE_1__*) ; 
 int update_context_from_thread (TYPE_5__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int update_context_from_user (TYPE_5__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int submit_packet(PerThreadContext *p, AVCodecContext *user_avctx,
                         AVPacket *avpkt)
{
    FrameThreadContext *fctx = p->parent;
    PerThreadContext *prev_thread = fctx->prev_thread;
    const AVCodec *codec = p->avctx->codec;
    int ret;

    if (!avpkt->size && !(codec->capabilities & AV_CODEC_CAP_DELAY))
        return 0;

    pthread_mutex_lock(&p->mutex);

    ret = update_context_from_user(p->avctx, user_avctx);
    if (ret) {
        pthread_mutex_unlock(&p->mutex);
        return ret;
    }
    atomic_store_explicit(&p->debug_threads,
                          (p->avctx->debug & FF_DEBUG_THREADS) != 0,
                          memory_order_relaxed);

    release_delayed_buffers(p);

    if (prev_thread) {
        int err;
        if (atomic_load(&prev_thread->state) == STATE_SETTING_UP) {
            pthread_mutex_lock(&prev_thread->progress_mutex);
            while (atomic_load(&prev_thread->state) == STATE_SETTING_UP)
                pthread_cond_wait(&prev_thread->progress_cond, &prev_thread->progress_mutex);
            pthread_mutex_unlock(&prev_thread->progress_mutex);
        }

        err = update_context_from_thread(p->avctx, prev_thread->avctx, 0);
        if (err) {
            pthread_mutex_unlock(&p->mutex);
            return err;
        }
    }

    av_packet_unref(&p->avpkt);
    ret = av_packet_ref(&p->avpkt, avpkt);
    if (ret < 0) {
        pthread_mutex_unlock(&p->mutex);
        av_log(p->avctx, AV_LOG_ERROR, "av_packet_ref() failed in submit_packet()\n");
        return ret;
    }

    atomic_store(&p->state, STATE_SETTING_UP);
    pthread_cond_signal(&p->input_cond);
    pthread_mutex_unlock(&p->mutex);

    /*
     * If the client doesn't have a thread-safe get_buffer(),
     * then decoding threads call back to the main thread,
     * and it calls back to the client here.
     */

    if (!p->avctx->thread_safe_callbacks && (
         p->avctx->get_format != avcodec_default_get_format ||
         p->avctx->get_buffer2 != avcodec_default_get_buffer2)) {
        while (atomic_load(&p->state) != STATE_SETUP_FINISHED && atomic_load(&p->state) != STATE_INPUT_READY) {
            int call_done = 1;
            pthread_mutex_lock(&p->progress_mutex);
            while (atomic_load(&p->state) == STATE_SETTING_UP)
                pthread_cond_wait(&p->progress_cond, &p->progress_mutex);

            switch (atomic_load_explicit(&p->state, memory_order_acquire)) {
            case STATE_GET_BUFFER:
                p->result = ff_get_buffer(p->avctx, p->requested_frame, p->requested_flags);
                break;
            case STATE_GET_FORMAT:
                p->result_format = ff_get_format(p->avctx, p->available_formats);
                break;
            default:
                call_done = 0;
                break;
            }
            if (call_done) {
                atomic_store(&p->state, STATE_SETTING_UP);
                pthread_cond_signal(&p->progress_cond);
            }
            pthread_mutex_unlock(&p->progress_mutex);
        }
    }

    fctx->prev_thread = p;
    fctx->next_decoding++;

    return 0;
}