#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  wait_queue; } ;
typedef  TYPE_1__ mq_cntrl ;

/* Variables and functions */
 int /*<<< orphan*/  LWP_MQ_STATUS_UNSATISFIED_NOWAIT ; 
 int /*<<< orphan*/  __lwp_threadqueue_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void __lwpmq_flush_waitthreads(mq_cntrl *mqueue)
{
	__lwp_threadqueue_flush(&mqueue->wait_queue,LWP_MQ_STATUS_UNSATISFIED_NOWAIT);
}