#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  action_func ;
struct TYPE_8__ {int active_thread_type; int thread_count; TYPE_1__* internal; } ;
struct TYPE_7__ {int job_size; int* rets; int /*<<< orphan*/  mainfunc; int /*<<< orphan*/  thread; int /*<<< orphan*/ * func; void* args; } ;
struct TYPE_6__ {TYPE_2__* thread_ctx; } ;
typedef  TYPE_2__ SliceThreadContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int FF_THREAD_SLICE ; 
 int avcodec_default_execute (TYPE_3__*,int /*<<< orphan*/ *,void*,int*,int,int) ; 
 int /*<<< orphan*/  avpriv_slicethread_execute (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int thread_execute(AVCodecContext *avctx, action_func* func, void *arg, int *ret, int job_count, int job_size)
{
    SliceThreadContext *c = avctx->internal->thread_ctx;

    if (!(avctx->active_thread_type&FF_THREAD_SLICE) || avctx->thread_count <= 1)
        return avcodec_default_execute(avctx, func, arg, ret, job_count, job_size);

    if (job_count <= 0)
        return 0;

    c->job_size = job_size;
    c->args = arg;
    c->func = func;
    c->rets = ret;

    avpriv_slicethread_execute(c->thread, job_count, !!c->mainfunc  );
    return 0;
}