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
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ object; int /*<<< orphan*/  tqueue; } ;
typedef  TYPE_2__ tqueue_st ;
typedef  int s32 ;
typedef  scalar_t__ lwpq_t ;

/* Variables and functions */
 int LWP_OBJMASKID (int /*<<< orphan*/ ) ; 
 int LWP_OBJMASKTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWP_OBJTYPE_TQUEUE ; 
 int /*<<< orphan*/  LWP_STATES_WAITING_ON_THREADQ ; 
 int /*<<< orphan*/  LWP_THREADQ_MODEFIFO ; 
 int /*<<< orphan*/  __lwp_thread_dispatchenable () ; 
 int /*<<< orphan*/  __lwp_threadqueue_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* __lwp_tqueue_allocate () ; 

s32 LWP_InitQueue(lwpq_t *thequeue)
{
	tqueue_st *tq;

	if(!thequeue) return -1;

	tq = __lwp_tqueue_allocate();
	if(!tq) return -1;

	__lwp_threadqueue_init(&tq->tqueue,LWP_THREADQ_MODEFIFO,LWP_STATES_WAITING_ON_THREADQ,0);

	*thequeue = (lwpq_t)(LWP_OBJMASKTYPE(LWP_OBJTYPE_TQUEUE)|LWP_OBJMASKID(tq->object.id));
	__lwp_thread_dispatchenable();

	return 0;
}