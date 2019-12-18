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
typedef  int s32 ;
typedef  scalar_t__ cond_t ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ object; int /*<<< orphan*/  wait_queue; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ cond_st ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  LWP_MUTEX_NULL ; 
 int LWP_OBJMASKID (int /*<<< orphan*/ ) ; 
 int LWP_OBJMASKTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWP_OBJTYPE_COND ; 
 int /*<<< orphan*/  LWP_STATES_WAITING_FOR_CONDVAR ; 
 int /*<<< orphan*/  LWP_THREADQ_MODEFIFO ; 
 TYPE_2__* __lwp_cond_allocate () ; 
 int /*<<< orphan*/  __lwp_thread_dispatchenable () ; 
 int /*<<< orphan*/  __lwp_threadqueue_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s32 LWP_CondInit(cond_t *cond)
{
	cond_st *ret;

	if(!cond) return -1;

	ret = __lwp_cond_allocate();
	if(!ret) return ENOMEM;

	ret->lock = LWP_MUTEX_NULL;
	__lwp_threadqueue_init(&ret->wait_queue,LWP_THREADQ_MODEFIFO,LWP_STATES_WAITING_FOR_CONDVAR,ETIMEDOUT);

	*cond = (cond_t)(LWP_OBJMASKTYPE(LWP_OBJTYPE_COND)|LWP_OBJMASKID(ret->object.id));
	__lwp_thread_dispatchenable();

	return 0;
}