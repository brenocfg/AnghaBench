#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  atomic_int ;
struct TYPE_9__ {TYPE_6__** owner; TYPE_1__* progress; } ;
typedef  TYPE_3__ ThreadFrame ;
struct TYPE_11__ {TYPE_2__* internal; } ;
struct TYPE_10__ {int /*<<< orphan*/  progress_mutex; int /*<<< orphan*/  progress_cond; int /*<<< orphan*/  debug_threads; } ;
struct TYPE_8__ {TYPE_4__* thread_ctx; } ;
struct TYPE_7__ {scalar_t__ data; } ;
typedef  TYPE_4__ PerThreadContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int atomic_load_explicit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_store_explicit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  memory_order_relaxed ; 
 int /*<<< orphan*/  memory_order_release ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void ff_thread_report_progress(ThreadFrame *f, int n, int field)
{
    PerThreadContext *p;
    atomic_int *progress = f->progress ? (atomic_int*)f->progress->data : NULL;

    if (!progress ||
        atomic_load_explicit(&progress[field], memory_order_relaxed) >= n)
        return;

    p = f->owner[field]->internal->thread_ctx;

    if (atomic_load_explicit(&p->debug_threads, memory_order_relaxed))
        av_log(f->owner[field], AV_LOG_DEBUG,
               "%p finished %d field %d\n", progress, n, field);

    pthread_mutex_lock(&p->progress_mutex);

    atomic_store_explicit(&progress[field], n, memory_order_release);

    pthread_cond_broadcast(&p->progress_cond);
    pthread_mutex_unlock(&p->progress_mutex);
}