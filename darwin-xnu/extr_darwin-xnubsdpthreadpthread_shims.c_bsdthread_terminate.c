#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_t ;
struct proc {int dummy; } ;
struct bsdthread_terminate_args {int /*<<< orphan*/  sem; int /*<<< orphan*/  port; int /*<<< orphan*/  freesize; int /*<<< orphan*/  stackaddr; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {int (* bsdthread_terminate ) (struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int THREAD_TAG_WORKQUEUE ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  get_bsdthread_info (int /*<<< orphan*/ ) ; 
 TYPE_1__* pthread_functions ; 
 int stub1 (struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int thread_get_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workq_thread_terminate (struct proc*,int /*<<< orphan*/ ) ; 

int
bsdthread_terminate(struct proc *p, struct bsdthread_terminate_args *uap, int32_t *retval)
{
	thread_t th = current_thread();
	if (thread_get_tag(th) & THREAD_TAG_WORKQUEUE) {
		workq_thread_terminate(p, get_bsdthread_info(th));
	}
	return pthread_functions->bsdthread_terminate(p, uap->stackaddr, uap->freesize, uap->port, uap->sem, retval);
}