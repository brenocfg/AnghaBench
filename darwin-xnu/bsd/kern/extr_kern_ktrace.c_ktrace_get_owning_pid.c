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
 int /*<<< orphan*/  ktrace_assert_lock_held () ; 
 int /*<<< orphan*/  ktrace_ownership_maintenance () ; 
 int ktrace_owning_pid ; 

int
ktrace_get_owning_pid(void)
{
	ktrace_assert_lock_held();

	ktrace_ownership_maintenance();
	return ktrace_owning_pid;
}