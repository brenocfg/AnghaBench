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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  kern_ctl_ref ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSDecrementAtomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mptcp_kern_skt_inuse ; 

__attribute__((used)) static errno_t
mptcp_symptoms_ctl_disconnect(kern_ctl_ref kctlref, u_int32_t kcunit,
	void *unitinfo)
{
#pragma unused(kctlref, kcunit, unitinfo)

	OSDecrementAtomic(&mptcp_kern_skt_inuse);

	return (0);
}