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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {TYPE_1__* dtrs; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {scalar_t__ page_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_TLB ; 
 int /*<<< orphan*/  PAGEALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thash_purge_entries (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vtr_find_overlap (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vcpu_ptr_d(struct kvm_vcpu *vcpu, u64 ifa, u64 ps)
{
	int index;
	u64 va;

	va = PAGEALIGN(ifa, ps);
	while ((index = vtr_find_overlap(vcpu, va, ps, D_TLB)) >= 0)
		vcpu->arch.dtrs[index].page_flags = 0;

	thash_purge_entries(vcpu, va, ps);
}