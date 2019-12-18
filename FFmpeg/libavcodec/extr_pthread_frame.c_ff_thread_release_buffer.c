#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_10__* f; int /*<<< orphan*/ ** owner; int /*<<< orphan*/  progress; } ;
typedef  TYPE_2__ ThreadFrame ;
struct TYPE_18__ {int active_thread_type; int debug; TYPE_1__* internal; } ;
struct TYPE_17__ {int /*<<< orphan*/  buffer_mutex; } ;
struct TYPE_16__ {int num_released_buffers; int /*<<< orphan*/ * released_buffers; int /*<<< orphan*/  released_buffers_allocated; TYPE_4__* parent; } ;
struct TYPE_14__ {TYPE_3__* thread_ctx; } ;
struct TYPE_13__ {int /*<<< orphan*/ * buf; } ;
typedef  TYPE_3__ PerThreadContext ;
typedef  TYPE_4__ FrameThreadContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int FF_DEBUG_BUFFERS ; 
 int FF_THREAD_FRAME ; 
 int INT_MAX ; 
 scalar_t__ THREAD_SAFE_CALLBACKS (TYPE_5__*) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * av_fast_realloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_frame_move_ref (int /*<<< orphan*/ *,TYPE_10__*) ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_10__*) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void ff_thread_release_buffer(AVCodecContext *avctx, ThreadFrame *f)
{
    PerThreadContext *p = avctx->internal->thread_ctx;
    FrameThreadContext *fctx;
    AVFrame *dst, *tmp;
    int can_direct_free = !(avctx->active_thread_type & FF_THREAD_FRAME) ||
                          THREAD_SAFE_CALLBACKS(avctx);

    if (!f->f || !f->f->buf[0])
        return;

    if (avctx->debug & FF_DEBUG_BUFFERS)
        av_log(avctx, AV_LOG_DEBUG, "thread_release_buffer called on pic %p\n", f);

    av_buffer_unref(&f->progress);
    f->owner[0] = f->owner[1] = NULL;

    if (can_direct_free) {
        av_frame_unref(f->f);
        return;
    }

    fctx = p->parent;
    pthread_mutex_lock(&fctx->buffer_mutex);

    if (p->num_released_buffers + 1 >= INT_MAX / sizeof(*p->released_buffers))
        goto fail;
    tmp = av_fast_realloc(p->released_buffers, &p->released_buffers_allocated,
                          (p->num_released_buffers + 1) *
                          sizeof(*p->released_buffers));
    if (!tmp)
        goto fail;
    p->released_buffers = tmp;

    dst = &p->released_buffers[p->num_released_buffers];
    av_frame_move_ref(dst, f->f);

    p->num_released_buffers++;

fail:
    pthread_mutex_unlock(&fctx->buffer_mutex);
}