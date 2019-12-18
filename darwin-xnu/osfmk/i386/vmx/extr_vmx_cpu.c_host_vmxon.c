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
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC ; 
 int /*<<< orphan*/  CPUMASK_ALL ; 
 int VMX_INUSE ; 
 int /*<<< orphan*/  VMX_KPRINTF (char*,int) ; 
 int VMX_OK ; 
 int VMX_UNSUPPORTED ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ get_preemption_level () ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_cpus_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmx_allocate_vmxon_regions () ; 
 scalar_t__ vmx_exclusive ; 
 int /*<<< orphan*/  vmx_globally_available () ; 
 int /*<<< orphan*/  vmx_lck_mtx ; 
 int /*<<< orphan*/  vmx_on ; 
 int vmx_use_count ; 

int
host_vmxon(boolean_t exclusive)
{
	int error;

	assert(0 == get_preemption_level());

	if (!vmx_globally_available())
		return VMX_UNSUPPORTED;

	lck_mtx_lock(vmx_lck_mtx);

	if (vmx_exclusive || (exclusive && vmx_use_count)) {
		error = VMX_INUSE;
	} else {
		if (0 == vmx_use_count) {
			vmx_allocate_vmxon_regions();
			vmx_exclusive = exclusive;
			vmx_use_count = 1;
			mp_cpus_call(CPUMASK_ALL, ASYNC, vmx_on, NULL);

		} else {
			vmx_use_count++;
		}

		VMX_KPRINTF("VMX use count: %d\n", vmx_use_count);
		error = VMX_OK;
	}

	lck_mtx_unlock(vmx_lck_mtx);

	return error;
}