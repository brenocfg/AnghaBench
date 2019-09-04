#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ priv_class; int /*<<< orphan*/  (* close ) (TYPE_2__*) ;} ;
struct TYPE_16__ {TYPE_5__* codec; scalar_t__ priv_data; TYPE_1__* internal; } ;
struct TYPE_15__ {int is_copy; int die; int /*<<< orphan*/  async_cond; int /*<<< orphan*/  async_mutex; int /*<<< orphan*/  hwaccel_mutex; int /*<<< orphan*/  buffer_mutex; struct TYPE_15__* threads; struct TYPE_15__* avctx; int /*<<< orphan*/  hw_frames_ctx; struct TYPE_15__* internal; struct TYPE_15__* slice_offset; struct TYPE_15__* priv_data; struct TYPE_15__* released_buffers; int /*<<< orphan*/  avpkt; int /*<<< orphan*/  output_cond; int /*<<< orphan*/  progress_cond; int /*<<< orphan*/  input_cond; int /*<<< orphan*/  progress_mutex; int /*<<< orphan*/  mutex; int /*<<< orphan*/  frame; scalar_t__ thread_init; int /*<<< orphan*/  thread; struct TYPE_15__* prev_thread; } ;
struct TYPE_14__ {TYPE_2__* thread_ctx; } ;
typedef  TYPE_2__ PerThreadContext ;
typedef  TYPE_2__ FrameThreadContext ;
typedef  TYPE_4__ AVCodecContext ;
typedef  TYPE_5__ AVCodec ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_opt_free (scalar_t__) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  park_frame_worker_threads (TYPE_2__*,int) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_delayed_buffers (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 scalar_t__ update_context_from_thread (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

void ff_frame_thread_free(AVCodecContext *avctx, int thread_count)
{
    FrameThreadContext *fctx = avctx->internal->thread_ctx;
    const AVCodec *codec = avctx->codec;
    int i;

    park_frame_worker_threads(fctx, thread_count);

    if (fctx->prev_thread && fctx->prev_thread != fctx->threads)
        if (update_context_from_thread(fctx->threads->avctx, fctx->prev_thread->avctx, 0) < 0) {
            av_log(avctx, AV_LOG_ERROR, "Final thread update failed\n");
            fctx->prev_thread->avctx->internal->is_copy = fctx->threads->avctx->internal->is_copy;
            fctx->threads->avctx->internal->is_copy = 1;
        }

    for (i = 0; i < thread_count; i++) {
        PerThreadContext *p = &fctx->threads[i];

        pthread_mutex_lock(&p->mutex);
        p->die = 1;
        pthread_cond_signal(&p->input_cond);
        pthread_mutex_unlock(&p->mutex);

        if (p->thread_init)
            pthread_join(p->thread, NULL);
        p->thread_init=0;

        if (codec->close && p->avctx)
            codec->close(p->avctx);

        release_delayed_buffers(p);
        av_frame_free(&p->frame);
    }

    for (i = 0; i < thread_count; i++) {
        PerThreadContext *p = &fctx->threads[i];

        pthread_mutex_destroy(&p->mutex);
        pthread_mutex_destroy(&p->progress_mutex);
        pthread_cond_destroy(&p->input_cond);
        pthread_cond_destroy(&p->progress_cond);
        pthread_cond_destroy(&p->output_cond);
        av_packet_unref(&p->avpkt);
        av_freep(&p->released_buffers);

        if (i && p->avctx) {
            av_freep(&p->avctx->priv_data);
            av_freep(&p->avctx->slice_offset);
        }

        if (p->avctx) {
            av_freep(&p->avctx->internal);
            av_buffer_unref(&p->avctx->hw_frames_ctx);
        }

        av_freep(&p->avctx);
    }

    av_freep(&fctx->threads);
    pthread_mutex_destroy(&fctx->buffer_mutex);
    pthread_mutex_destroy(&fctx->hwaccel_mutex);
    pthread_mutex_destroy(&fctx->async_mutex);
    pthread_cond_destroy(&fctx->async_cond);

    av_freep(&avctx->internal->thread_ctx);

    if (avctx->priv_data && avctx->codec && avctx->codec->priv_class)
        av_opt_free(avctx->priv_data);
    avctx->codec = NULL;
}