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

/* Variables and functions */
 int /*<<< orphan*/  MP_SPIN_TRIES ; 
 scalar_t__ __commpage_setup ; 
 int __system_power_source ; 
 int /*<<< orphan*/  commpage_set_spin_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
post_sys_powersource_internal(int i, int internal)
{
	if (internal == 0)
		__system_power_source = i;

	if (__commpage_setup != 0) {
		if (__system_power_source != 0)
			commpage_set_spin_count(0);
		else
			commpage_set_spin_count(MP_SPIN_TRIES);
	}
}