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
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  cpu_update ; 
 int /*<<< orphan*/  mp_broadcast (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ register_locks () ; 
 int /*<<< orphan*/  ucode_cpuid_set_info () ; 

__attribute__((used)) static void
xcpu_update(void)
{
	if (register_locks() != KERN_SUCCESS)
		return;

	/* Get all CPUs to perform the update */
	mp_broadcast(cpu_update, NULL);

	/* Update the cpuid info */
	ucode_cpuid_set_info();
}