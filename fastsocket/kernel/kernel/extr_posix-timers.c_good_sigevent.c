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
struct task_struct {int dummy; } ;
struct pid {int dummy; } ;
struct TYPE_5__ {int sigev_notify; scalar_t__ sigev_signo; int /*<<< orphan*/  sigev_notify_thread_id; } ;
typedef  TYPE_1__ sigevent_t ;
struct TYPE_6__ {struct task_struct* group_leader; } ;

/* Variables and functions */
 int SIGEV_NONE ; 
 int SIGEV_SIGNAL ; 
 int SIGEV_THREAD_ID ; 
 scalar_t__ SIGRTMAX ; 
 TYPE_2__* current ; 
 struct task_struct* find_task_by_vpid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  same_thread_group (struct task_struct*,TYPE_2__*) ; 
 struct pid* task_pid (struct task_struct*) ; 

__attribute__((used)) static struct pid *good_sigevent(sigevent_t * event)
{
	struct task_struct *rtn = current->group_leader;

	if ((event->sigev_notify & SIGEV_THREAD_ID ) &&
		(!(rtn = find_task_by_vpid(event->sigev_notify_thread_id)) ||
		 !same_thread_group(rtn, current) ||
		 (event->sigev_notify & ~SIGEV_THREAD_ID) != SIGEV_SIGNAL))
		return NULL;

	if (((event->sigev_notify & ~SIGEV_THREAD_ID) != SIGEV_NONE) &&
	    ((event->sigev_signo <= 0) || (event->sigev_signo > SIGRTMAX)))
		return NULL;

	return task_pid(rtn);
}