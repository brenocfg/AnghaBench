#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* threads; } ;
struct TYPE_6__ {scalar_t__ got_frame; int /*<<< orphan*/  progress_mutex; int /*<<< orphan*/  output_cond; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ PerThreadContext ;
typedef  TYPE_2__ FrameThreadContext ;

/* Variables and functions */
 scalar_t__ STATE_INPUT_READY ; 
 int /*<<< orphan*/  async_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  async_unlock (TYPE_2__*) ; 
 scalar_t__ atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void park_frame_worker_threads(FrameThreadContext *fctx, int thread_count)
{
    int i;

    async_unlock(fctx);

    for (i = 0; i < thread_count; i++) {
        PerThreadContext *p = &fctx->threads[i];

        if (atomic_load(&p->state) != STATE_INPUT_READY) {
            pthread_mutex_lock(&p->progress_mutex);
            while (atomic_load(&p->state) != STATE_INPUT_READY)
                pthread_cond_wait(&p->output_cond, &p->progress_mutex);
            pthread_mutex_unlock(&p->progress_mutex);
        }
        p->got_frame = 0;
    }

    async_lock(fctx);
}