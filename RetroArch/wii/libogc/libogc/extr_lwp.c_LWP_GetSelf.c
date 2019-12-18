#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ lwp_t ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 int LWP_OBJMASKID (int /*<<< orphan*/ ) ; 
 int LWP_OBJMASKTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWP_OBJTYPE_THREAD ; 
 int /*<<< orphan*/  __lwp_thread_dispatchdisable () ; 
 int /*<<< orphan*/  __lwp_thread_dispatchunnest () ; 
 TYPE_2__* _thr_executing ; 

lwp_t LWP_GetSelf()
{
	lwp_t ret;

	__lwp_thread_dispatchdisable();
	ret = (lwp_t)(LWP_OBJMASKTYPE(LWP_OBJTYPE_THREAD)|LWP_OBJMASKID(_thr_executing->object.id));
	__lwp_thread_dispatchunnest();

	return ret;
}