#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_8__ {TYPE_1__ object; int /*<<< orphan*/  sema; } ;
typedef  TYPE_3__ sema_st ;
typedef  int /*<<< orphan*/  sem_t ;
typedef  int s32 ;
struct TYPE_7__ {int ret_code; } ;
struct TYPE_9__ {TYPE_2__ wait; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ETIMEDOUT ; 
#define  LWP_SEMA_DELETED 131 
#define  LWP_SEMA_SUCCESSFUL 130 
#define  LWP_SEMA_TIMEOUT 129 
#define  LWP_SEMA_UNSATISFIED_NOWAIT 128 
 int /*<<< orphan*/  LWP_THREADQ_NOTIMEOUT ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__* __lwp_sema_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_sema_seize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_thread_dispatchenable () ; 
 TYPE_4__* _thr_executing ; 

s32 LWP_SemWait(sem_t sem)
{
	sema_st *lwp_sem = __lwp_sema_open(sem);
	if(!lwp_sem) return -1;

	__lwp_sema_seize(&lwp_sem->sema,lwp_sem->object.id,TRUE,LWP_THREADQ_NOTIMEOUT);
	__lwp_thread_dispatchenable();

	switch(_thr_executing->wait.ret_code) {
		case LWP_SEMA_SUCCESSFUL:
			break;
		case LWP_SEMA_UNSATISFIED_NOWAIT:
			return EAGAIN;
		case LWP_SEMA_DELETED:
			return EAGAIN;
		case LWP_SEMA_TIMEOUT:
			return ETIMEDOUT;

	}
	return 0;
}