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
typedef  int s32 ;
typedef  scalar_t__ mutex_t ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_7__ {TYPE_1__ object; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ mutex_st ;
struct TYPE_8__ {int prioceil; int /*<<< orphan*/  onlyownerrelease; int /*<<< orphan*/  nest_behavior; int /*<<< orphan*/  mode; } ;
typedef  TYPE_3__ lwp_mutex_attr ;

/* Variables and functions */
 int /*<<< orphan*/  LWP_MUTEX_FIFO ; 
 int /*<<< orphan*/  LWP_MUTEX_NEST_ACQUIRE ; 
 int /*<<< orphan*/  LWP_MUTEX_NEST_ERROR ; 
 int /*<<< orphan*/  LWP_MUTEX_UNLOCKED ; 
 int LWP_OBJMASKID (int /*<<< orphan*/ ) ; 
 int LWP_OBJMASKTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWP_OBJTYPE_MUTEX ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* __lwp_mutex_allocate () ; 
 int /*<<< orphan*/  __lwp_mutex_initialize (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_thread_dispatchunnest () ; 

s32 LWP_MutexInit(mutex_t *mutex,bool use_recursive)
{
	lwp_mutex_attr attr;
	mutex_st *ret;

	if(!mutex) return -1;

	ret = __lwp_mutex_allocate();
	if(!ret) return -1;

	attr.mode = LWP_MUTEX_FIFO;
	attr.nest_behavior = use_recursive?LWP_MUTEX_NEST_ACQUIRE:LWP_MUTEX_NEST_ERROR;
	attr.onlyownerrelease = TRUE;
	attr.prioceil = 1; //__lwp_priotocore(LWP_PRIO_MAX-1);
	__lwp_mutex_initialize(&ret->mutex,&attr,LWP_MUTEX_UNLOCKED);

	*mutex = (mutex_t)(LWP_OBJMASKTYPE(LWP_OBJTYPE_MUTEX)|LWP_OBJMASKID(ret->object.id));
	__lwp_thread_dispatchunnest();
	return 0;
}