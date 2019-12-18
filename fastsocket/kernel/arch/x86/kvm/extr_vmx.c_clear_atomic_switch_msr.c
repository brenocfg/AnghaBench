#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct msr_autoload {unsigned int nr; int /*<<< orphan*/ * host; TYPE_1__* guest; } ;
struct vcpu_vmx {struct msr_autoload msr_autoload; } ;
struct TYPE_2__ {unsigned int index; } ;

/* Variables and functions */
#define  MSR_CORE_PERF_GLOBAL_CTRL 128 
 int /*<<< orphan*/  VM_ENTRY_LOAD_IA32_PERF_GLOBAL_CTRL ; 
 int /*<<< orphan*/  VM_ENTRY_MSR_LOAD_COUNT ; 
 int /*<<< orphan*/  VM_EXIT_LOAD_IA32_PERF_GLOBAL_CTRL ; 
 int /*<<< orphan*/  VM_EXIT_MSR_LOAD_COUNT ; 
 int /*<<< orphan*/  clear_atomic_switch_msr_special (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_has_load_perf_global_ctrl ; 
 int /*<<< orphan*/  vmcs_write32 (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void clear_atomic_switch_msr(struct vcpu_vmx *vmx, unsigned msr)
{
	unsigned i;
	struct msr_autoload *m = &vmx->msr_autoload;

	switch (msr) {
	case MSR_CORE_PERF_GLOBAL_CTRL:
		if (cpu_has_load_perf_global_ctrl) {
			clear_atomic_switch_msr_special(
					VM_ENTRY_LOAD_IA32_PERF_GLOBAL_CTRL,
					VM_EXIT_LOAD_IA32_PERF_GLOBAL_CTRL);
			return;
		}
		break;
	}

	for (i = 0; i < m->nr; ++i)
		if (m->guest[i].index == msr)
			break;

	if (i == m->nr)
		return;
	--m->nr;
	m->guest[i] = m->guest[m->nr];
	m->host[i] = m->host[m->nr];
	vmcs_write32(VM_ENTRY_MSR_LOAD_COUNT, m->nr);
	vmcs_write32(VM_EXIT_MSR_LOAD_COUNT, m->nr);
}