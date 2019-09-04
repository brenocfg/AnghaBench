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
typedef  int /*<<< orphan*/  action_func2 ;
struct TYPE_8__ {TYPE_1__* internal; } ;
struct TYPE_7__ {int /*<<< orphan*/ * func2; } ;
struct TYPE_6__ {TYPE_2__* thread_ctx; } ;
typedef  TYPE_2__ SliceThreadContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int thread_execute (TYPE_3__*,int /*<<< orphan*/ *,void*,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int thread_execute2(AVCodecContext *avctx, action_func2* func2, void *arg, int *ret, int job_count)
{
    SliceThreadContext *c = avctx->internal->thread_ctx;
    c->func2 = func2;
    return thread_execute(avctx, NULL, arg, ret, job_count, 0);
}