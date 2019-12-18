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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  tc_regions; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  REGION_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ vcpu_quick_region_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhpt_purge (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtlb_purge (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void thash_purge_entries_remote(struct kvm_vcpu *v, u64 va, u64 ps)
{
	u64 old_va = va;
	va = REGION_OFFSET(va);
	if (vcpu_quick_region_check(v->arch.tc_regions, old_va))
		vtlb_purge(v, va, ps);
	vhpt_purge(v, va, ps);
}