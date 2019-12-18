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
 int /*<<< orphan*/  ASYNC ; 
 int /*<<< orphan*/  CPUMASK_ALL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  VMX_KPRINTF (char*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ get_preemption_level () ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_cpus_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmx_exclusive ; 
 int /*<<< orphan*/  vmx_free_vmxon_regions () ; 
 int /*<<< orphan*/  vmx_lck_mtx ; 
 int /*<<< orphan*/  vmx_off ; 
 int vmx_use_count ; 

void
host_vmxoff()
{
	assert(0 == get_preemption_level());

	lck_mtx_lock(vmx_lck_mtx);

	if (1 == vmx_use_count) {
		vmx_exclusive = FALSE;
		vmx_use_count = 0;
		mp_cpus_call(CPUMASK_ALL, ASYNC, vmx_off, NULL);
		vmx_free_vmxon_regions();
	} else {
		vmx_use_count--;
	}

	lck_mtx_unlock(vmx_lck_mtx);

	VMX_KPRINTF("VMX use count: %d\n", vmx_use_count);
}