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
typedef  int /*<<< orphan*/  mqbox_t ;
typedef  int /*<<< orphan*/  mqbox_st ;

/* Variables and functions */
 int /*<<< orphan*/  LWP_CHECK_MBOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWP_OBJMASKID (int /*<<< orphan*/ ) ; 
 scalar_t__ __lwp_objmgr_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _lwp_mqbox_objects ; 

__attribute__((used)) static __inline__ mqbox_st* __lwp_mqbox_open(mqbox_t mbox)
{
	LWP_CHECK_MBOX(mbox);
	return (mqbox_st*)__lwp_objmgr_get(&_lwp_mqbox_objects,LWP_OBJMASKID(mbox));
}