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
struct sockaddr_ctl {scalar_t__ sc_unit; } ;
typedef  int /*<<< orphan*/  kern_ctl_ref ;
typedef  int /*<<< orphan*/  errno_t ;
typedef  scalar_t__ UInt32 ;

/* Variables and functions */
 int /*<<< orphan*/  EALREADY ; 
 scalar_t__ OSCompareAndSwap (scalar_t__,scalar_t__,scalar_t__*) ; 
 scalar_t__ TCP_CCDBG_NOUNIT ; 
 scalar_t__ tcp_ccdbg_unit ; 

__attribute__((used)) static errno_t
tcp_ccdbg_control_connect(kern_ctl_ref kctl, struct sockaddr_ctl *sac,
	void **uinfo)
{
#pragma unused(kctl)
#pragma unused(uinfo)

	UInt32 old_value = TCP_CCDBG_NOUNIT;
	UInt32 new_value = sac->sc_unit;

	if (tcp_ccdbg_unit != old_value)
		return (EALREADY);

	if (OSCompareAndSwap(old_value, new_value, &tcp_ccdbg_unit))
		return (0);
	else
		return (EALREADY);
}