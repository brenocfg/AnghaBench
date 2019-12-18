#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  msq_buffers; int /*<<< orphan*/  wait_queue; } ;
typedef  TYPE_1__ mq_cntrl ;

/* Variables and functions */
 int /*<<< orphan*/  __lwp_threadqueue_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_wkspace_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwpmq_flush_support (TYPE_1__*) ; 

void __lwpmq_close(mq_cntrl *mqueue,u32 status)
{
	__lwp_threadqueue_flush(&mqueue->wait_queue,status);
	__lwpmq_flush_support(mqueue);
	__lwp_wkspace_free(mqueue->msq_buffers);
}