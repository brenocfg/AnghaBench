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

/* Variables and functions */

__attribute__((used)) static void
necp_ctl_rcvd(kern_ctl_ref kctlref, u_int32_t unit, void *unitinfo, int flags)
{
#pragma unused(kctlref, unit, unitinfo, flags)
	return;
}