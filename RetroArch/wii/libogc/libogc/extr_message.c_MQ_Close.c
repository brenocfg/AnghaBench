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
typedef  int /*<<< orphan*/  mqbox_t ;
struct TYPE_4__ {int /*<<< orphan*/  mqueue; } ;
typedef  TYPE_1__ mqbox_st ;

/* Variables and functions */
 int /*<<< orphan*/  __lwp_mqbox_free (TYPE_1__*) ; 
 TYPE_1__* __lwp_mqbox_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_thread_dispatchenable () ; 
 int /*<<< orphan*/  __lwpmq_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void MQ_Close(mqbox_t mqbox)
{
	mqbox_st *mbox;

	mbox = __lwp_mqbox_open(mqbox);
	if(!mbox) return;

	__lwpmq_close(&mbox->mqueue,0);
	__lwp_thread_dispatchenable();

	__lwp_mqbox_free(mbox);
}