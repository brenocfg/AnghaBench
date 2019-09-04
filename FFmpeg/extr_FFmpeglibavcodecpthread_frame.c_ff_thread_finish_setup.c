#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  hwaccel_mutex; } ;
struct TYPE_11__ {int active_thread_type; TYPE_2__* hwaccel; TYPE_1__* internal; } ;
struct TYPE_10__ {int hwaccel_serializing; int async_serializing; int /*<<< orphan*/  progress_mutex; int /*<<< orphan*/  progress_cond; int /*<<< orphan*/  state; TYPE_7__* parent; } ;
struct TYPE_9__ {int caps_internal; } ;
struct TYPE_8__ {TYPE_3__* thread_ctx; } ;
typedef  TYPE_3__ PerThreadContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int FF_THREAD_FRAME ; 
 int HWACCEL_CAP_ASYNC_SAFE ; 
 scalar_t__ STATE_SETUP_FINISHED ; 
 int /*<<< orphan*/  async_lock (TYPE_7__*) ; 
 scalar_t__ atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void ff_thread_finish_setup(AVCodecContext *avctx) {
    PerThreadContext *p = avctx->internal->thread_ctx;

    if (!(avctx->active_thread_type&FF_THREAD_FRAME)) return;

    if (avctx->hwaccel && !p->hwaccel_serializing) {
        pthread_mutex_lock(&p->parent->hwaccel_mutex);
        p->hwaccel_serializing = 1;
    }

    /* this assumes that no hwaccel calls happen before ff_thread_finish_setup() */
    if (avctx->hwaccel &&
        !(avctx->hwaccel->caps_internal & HWACCEL_CAP_ASYNC_SAFE)) {
        p->async_serializing = 1;

        async_lock(p->parent);
    }

    pthread_mutex_lock(&p->progress_mutex);
    if(atomic_load(&p->state) == STATE_SETUP_FINISHED){
        av_log(avctx, AV_LOG_WARNING, "Multiple ff_thread_finish_setup() calls\n");
    }

    atomic_store(&p->state, STATE_SETUP_FINISHED);

    pthread_cond_broadcast(&p->progress_cond);
    pthread_mutex_unlock(&p->progress_mutex);
}