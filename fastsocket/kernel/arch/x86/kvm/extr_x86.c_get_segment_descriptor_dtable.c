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
typedef  int u16 ;
struct kvm_vcpu {int dummy; } ;
struct kvm_segment {int /*<<< orphan*/  base; int /*<<< orphan*/  limit; scalar_t__ unusable; } ;
struct descriptor_table {int /*<<< orphan*/  base; int /*<<< orphan*/  limit; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_gdt ) (struct kvm_vcpu*,struct descriptor_table*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_SREG_LDTR ; 
 int /*<<< orphan*/  kvm_get_segment (struct kvm_vcpu*,struct kvm_segment*,int /*<<< orphan*/ ) ; 
 TYPE_1__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,struct descriptor_table*) ; 

__attribute__((used)) static void get_segment_descriptor_dtable(struct kvm_vcpu *vcpu,
					  u16 selector,
					  struct descriptor_table *dtable)
{
	if (selector & 1 << 2) {
		struct kvm_segment kvm_seg;

		kvm_get_segment(vcpu, &kvm_seg, VCPU_SREG_LDTR);

		if (kvm_seg.unusable)
			dtable->limit = 0;
		else
			dtable->limit = kvm_seg.limit;
		dtable->base = kvm_seg.base;
	}
	else
		kvm_x86_ops->get_gdt(vcpu, dtable);
}