#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  avfilter_action_func ;
struct TYPE_8__ {int* rets; int /*<<< orphan*/  thread; int /*<<< orphan*/ * func; void* arg; TYPE_4__* ctx; } ;
typedef  TYPE_3__ ThreadContext ;
struct TYPE_9__ {TYPE_2__* graph; } ;
struct TYPE_7__ {TYPE_1__* internal; } ;
struct TYPE_6__ {TYPE_3__* thread; } ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  avpriv_slicethread_execute (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int thread_execute(AVFilterContext *ctx, avfilter_action_func *func,
                          void *arg, int *ret, int nb_jobs)
{
    ThreadContext *c = ctx->graph->internal->thread;

    if (nb_jobs <= 0)
        return 0;
    c->ctx         = ctx;
    c->arg         = arg;
    c->func        = func;
    c->rets        = ret;

    avpriv_slicethread_execute(c->thread, nb_jobs, 0);
    return 0;
}