#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_3__ {scalar_t__ shadow_root_level; int /*<<< orphan*/ * pae_root; int /*<<< orphan*/  root_hpa; } ;
struct TYPE_4__ {TYPE_1__ mmu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct kvm_shadow_walk_iterator {int addr; scalar_t__ level; int /*<<< orphan*/  shadow_addr; } ;

/* Variables and functions */
 scalar_t__ PT32E_ROOT_LEVEL ; 
 int /*<<< orphan*/  PT64_BASE_ADDR_MASK ; 

__attribute__((used)) static void shadow_walk_init(struct kvm_shadow_walk_iterator *iterator,
			     struct kvm_vcpu *vcpu, u64 addr)
{
	iterator->addr = addr;
	iterator->shadow_addr = vcpu->arch.mmu.root_hpa;
	iterator->level = vcpu->arch.mmu.shadow_root_level;
	if (iterator->level == PT32E_ROOT_LEVEL) {
		iterator->shadow_addr
			= vcpu->arch.mmu.pae_root[(addr >> 30) & 3];
		iterator->shadow_addr &= PT64_BASE_ADDR_MASK;
		--iterator->level;
		if (!iterator->shadow_addr)
			iterator->level = 0;
	}
}