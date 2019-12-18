#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  lwp_thrqueue ;
struct TYPE_4__ {int /*<<< orphan*/  ret_code; } ;
struct TYPE_5__ {TYPE_1__ wait; } ;
typedef  TYPE_2__ lwp_cntrl ;

/* Variables and functions */
 TYPE_2__* __lwp_threadqueue_dequeue (int /*<<< orphan*/ *) ; 

void __lwp_threadqueue_flush(lwp_thrqueue *queue,u32 status)
{
	lwp_cntrl *thethread;
	while((thethread=__lwp_threadqueue_dequeue(queue))) {
		thethread->wait.ret_code = status;
	}
}