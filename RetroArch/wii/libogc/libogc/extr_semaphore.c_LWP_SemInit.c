#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_7__ {TYPE_1__ object; int /*<<< orphan*/  sema; } ;
typedef  TYPE_2__ sema_st ;
typedef  scalar_t__ sem_t ;
typedef  int s32 ;
struct TYPE_8__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  max_cnt; } ;
typedef  TYPE_3__ lwp_semattr ;

/* Variables and functions */
 int LWP_OBJMASKID (int /*<<< orphan*/ ) ; 
 int LWP_OBJMASKTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWP_OBJTYPE_SEM ; 
 int /*<<< orphan*/  LWP_SEMA_MODEFIFO ; 
 TYPE_2__* __lwp_sema_allocate () ; 
 int /*<<< orphan*/  __lwp_sema_initialize (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_thread_dispatchenable () ; 

s32 LWP_SemInit(sem_t *sem,u32 start,u32 max)
{
	lwp_semattr attr;
	sema_st *ret;

	if(!sem) return -1;

	ret = __lwp_sema_allocate();
	if(!ret) return -1;

	attr.max_cnt = max;
	attr.mode = LWP_SEMA_MODEFIFO;
	__lwp_sema_initialize(&ret->sema,&attr,start);

	*sem = (sem_t)(LWP_OBJMASKTYPE(LWP_OBJTYPE_SEM)|LWP_OBJMASKID(ret->object.id));
	__lwp_thread_dispatchenable();
	return 0;
}