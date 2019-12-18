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
typedef  int u64 ;
struct TYPE_2__ {int* last_pte_updated; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int shadow_accessed_mask ; 

__attribute__((used)) static bool last_updated_pte_accessed(struct kvm_vcpu *vcpu)
{
	u64 *spte = vcpu->arch.last_pte_updated;

	return !!(spte && (*spte & shadow_accessed_mask));
}