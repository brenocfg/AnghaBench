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
struct TYPE_2__ {unsigned long cr4; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 unsigned long X86_CR4_PAE ; 
 unsigned long X86_CR4_PSE ; 
 int /*<<< orphan*/  is_paging (struct kvm_vcpu*) ; 

__attribute__((used)) static void ept_update_paging_mode_cr4(unsigned long *hw_cr4,
					struct kvm_vcpu *vcpu)
{
	if (!is_paging(vcpu)) {
		*hw_cr4 &= ~X86_CR4_PAE;
		*hw_cr4 |= X86_CR4_PSE;
	} else if (!(vcpu->arch.cr4 & X86_CR4_PAE))
		*hw_cr4 &= ~X86_CR4_PAE;
}