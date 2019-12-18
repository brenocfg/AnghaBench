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
typedef  int /*<<< orphan*/  u64 ;
struct vmcs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_cpu_vmxoff () ; 
 int /*<<< orphan*/  kvm_cpu_vmxon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  per_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 
 int /*<<< orphan*/  vmcs_clear (struct vmcs*) ; 
 int /*<<< orphan*/  vmm_exclusive ; 
 int /*<<< orphan*/  vmxarea ; 

__attribute__((used)) static inline void vmcs_init(struct vmcs *vmcs)
{
	u64 phys_addr = __pa(per_cpu(vmxarea, raw_smp_processor_id()));

	if (!vmm_exclusive)
		kvm_cpu_vmxon(phys_addr);

	vmcs_clear(vmcs);

	if (!vmm_exclusive)
		kvm_cpu_vmxoff();
}