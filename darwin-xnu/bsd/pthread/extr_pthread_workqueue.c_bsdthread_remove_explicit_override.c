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
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  scalar_t__ thread_t ;
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
struct TYPE_3__ {int /*<<< orphan*/  task; } ;

/* Variables and functions */
 int ESRCH ; 
 scalar_t__ THREAD_NULL ; 
 int /*<<< orphan*/  THREAD_QOS_OVERRIDE_TYPE_PTHREAD_EXPLICIT_OVERRIDE ; 
 scalar_t__ port_name_to_thread (int /*<<< orphan*/ ) ; 
 int proc_thread_qos_remove_override (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_deallocate (scalar_t__) ; 

__attribute__((used)) static int
bsdthread_remove_explicit_override(proc_t p, mach_port_name_t kport,
		user_addr_t resource)
{
	thread_t th = port_name_to_thread(kport);
	if (th == THREAD_NULL) {
		return ESRCH;
	}

	int rv = proc_thread_qos_remove_override(p->task, th, 0, resource,
			THREAD_QOS_OVERRIDE_TYPE_PTHREAD_EXPLICIT_OVERRIDE);

	thread_deallocate(th);
	return rv;
}