#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int s32 ;
typedef  scalar_t__ mutex_t ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_7__ {TYPE_1__ object; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_3__ mutex_st ;
struct TYPE_6__ {int ret_code; } ;
struct TYPE_8__ {TYPE_2__ wait; } ;

/* Variables and functions */
 scalar_t__ LWP_MUTEX_NULL ; 
 int /*<<< orphan*/  LWP_OBJMASKID (scalar_t__) ; 
 scalar_t__ LWP_OBJTYPE (scalar_t__) ; 
 scalar_t__ LWP_OBJTYPE_MUTEX ; 
 int /*<<< orphan*/  __lwp_mutex_seize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __lwp_objmgr_getisrdisable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _lwp_mutex_objects ; 
 TYPE_4__* _thr_executing ; 

__attribute__((used)) static s32 __lwp_mutex_locksupp(mutex_t lock,u32 timeout,u8 block)
{
	u32 level;
	mutex_st *p;

	if(lock==LWP_MUTEX_NULL || LWP_OBJTYPE(lock)!=LWP_OBJTYPE_MUTEX) return -1;

	p = (mutex_st*)__lwp_objmgr_getisrdisable(&_lwp_mutex_objects,LWP_OBJMASKID(lock),&level);
	if(!p) return -1;

	__lwp_mutex_seize(&p->mutex,p->object.id,block,timeout,level);
	return _thr_executing->wait.ret_code;
}