#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wait_interrupt_t ;
typedef  TYPE_2__* thread_t ;
struct task {scalar_t__ itk_space; } ;
typedef  int mach_exception_data_type_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_3__* ipc_port_t ;
typedef  TYPE_4__* host_priv_t ;
struct TYPE_15__ {TYPE_3__* port; } ;
struct TYPE_14__ {int /*<<< orphan*/  lock; TYPE_9__* exc_actions; } ;
struct TYPE_11__ {scalar_t__ receiver; } ;
struct TYPE_13__ {TYPE_1__ data; } ;
struct TYPE_12__ {struct task* task; } ;

/* Variables and functions */
 int EXCEPTION_CODE_MAX ; 
 size_t EXC_RPC_ALERT ; 
 int /*<<< orphan*/  IP_VALID (TYPE_3__*) ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 int /*<<< orphan*/  exception_deliver (TYPE_2__*,size_t,int*,int,TYPE_9__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* host_priv_self () ; 
 int /*<<< orphan*/  ip_active (TYPE_3__*) ; 
 int /*<<< orphan*/  thread_interrupt_level (int /*<<< orphan*/ ) ; 

kern_return_t sys_perf_notify(thread_t thread, int pid) 
{
	host_priv_t		hostp;
	ipc_port_t		xport;
	wait_interrupt_t	wsave;
	kern_return_t		ret;

	hostp = host_priv_self();	/* Get the host privileged ports */
	mach_exception_data_type_t	code[EXCEPTION_CODE_MAX];
	code[0] = 0xFF000001;		/* Set terminate code */
	code[1] = pid;		/* Pass out the pid */

	struct task *task = thread->task;
	xport = hostp->exc_actions[EXC_RPC_ALERT].port;	

	/* Make sure we're not catching our own exception */
	if (!IP_VALID(xport) ||
			!ip_active(xport) ||
			task->itk_space == xport->data.receiver) {

		return(KERN_FAILURE);	
	}

	wsave = thread_interrupt_level(THREAD_UNINT);	
	ret = exception_deliver(
			thread,
			EXC_RPC_ALERT, 
			code, 
			2, 
			hostp->exc_actions,
			&hostp->lock);
	(void)thread_interrupt_level(wsave);

	return(ret);
}