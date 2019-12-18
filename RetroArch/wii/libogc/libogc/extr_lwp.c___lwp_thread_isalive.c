#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ lwp_t ;
struct TYPE_2__ {int* stack; int /*<<< orphan*/  cur_state; } ;
typedef  TYPE_1__ lwp_cntrl ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LWP_OBJMASKID (scalar_t__) ; 
 scalar_t__ LWP_OBJTYPE (scalar_t__) ; 
 scalar_t__ LWP_OBJTYPE_THREAD ; 
 scalar_t__ LWP_THREAD_NULL ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ __lwp_objmgr_getnoprotection (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_statedormant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_statetransient (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _lwp_thr_objects ; 

BOOL __lwp_thread_isalive(lwp_t thr_id)
{
	if(thr_id==LWP_THREAD_NULL || LWP_OBJTYPE(thr_id)!=LWP_OBJTYPE_THREAD) return FALSE;

	lwp_cntrl *thethread = (lwp_cntrl*)__lwp_objmgr_getnoprotection(&_lwp_thr_objects,LWP_OBJMASKID(thr_id));

	if(thethread) {
		u32 *stackbase = thethread->stack;
		if(stackbase[0]==0xDEADBABE && !__lwp_statedormant(thethread->cur_state) && !__lwp_statetransient(thethread->cur_state))
			return TRUE;
	}

	return FALSE;
}