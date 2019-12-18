#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lwp_t ;
typedef  int /*<<< orphan*/  lwp_cntrl ;

/* Variables and functions */
 int /*<<< orphan*/  LWP_CHECK_THREAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWP_OBJMASKID (int /*<<< orphan*/ ) ; 
 scalar_t__ __lwp_objmgr_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _lwp_thr_objects ; 

__attribute__((used)) static __inline__ lwp_cntrl* __lwp_cntrl_open(lwp_t thr_id)
{
	LWP_CHECK_THREAD(thr_id);
	return (lwp_cntrl*)__lwp_objmgr_get(&_lwp_thr_objects,LWP_OBJMASKID(thr_id));
}