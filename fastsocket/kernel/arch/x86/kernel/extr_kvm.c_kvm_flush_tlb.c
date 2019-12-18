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
struct TYPE_2__ {int /*<<< orphan*/  op; } ;
struct kvm_mmu_op_flush_tlb {TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_MMU_OP_FLUSH_TLB ; 
 int /*<<< orphan*/  kvm_deferred_mmu_op (struct kvm_mmu_op_flush_tlb*,int) ; 

__attribute__((used)) static void kvm_flush_tlb(void)
{
	struct kvm_mmu_op_flush_tlb ftlb = {
		.header.op = KVM_MMU_OP_FLUSH_TLB,
	};

	kvm_deferred_mmu_op(&ftlb, sizeof ftlb);
}