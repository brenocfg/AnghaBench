#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  TYPE_2__* thread_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_6__ {TYPE_1__* th_work_interval; } ;
struct TYPE_5__ {scalar_t__ wi_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  thread_set_work_interval (TYPE_2__*,int /*<<< orphan*/ *) ; 

kern_return_t
kern_work_interval_destroy(thread_t thread, uint64_t work_interval_id)
{
	if (work_interval_id == 0)
		return KERN_INVALID_ARGUMENT;

	if (thread->th_work_interval == NULL ||
	    thread->th_work_interval->wi_id != work_interval_id) {
		/* work ID isn't valid or doesn't match joined work interval ID */
		return (KERN_INVALID_ARGUMENT);
	}

	thread_set_work_interval(thread, NULL);

	return KERN_SUCCESS;
}