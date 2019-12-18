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
typedef  int u16 ;
struct kvm_vcpu {int dummy; } ;
struct descriptor_table {int limit; scalar_t__ base; } ;
struct desc_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_segment_descriptor_dtable (struct kvm_vcpu*,int,struct descriptor_table*) ; 
 int kvm_write_guest_virt (scalar_t__,struct desc_struct*,int,struct kvm_vcpu*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int save_guest_segment_descriptor(struct kvm_vcpu *vcpu, u16 selector,
					 struct desc_struct *seg_desc)
{
	struct descriptor_table dtable;
	u16 index = selector >> 3;

	get_segment_descriptor_dtable(vcpu, selector, &dtable);

	if (dtable.limit < index * 8 + 7)
		return 1;
	return kvm_write_guest_virt(dtable.base + index*8, seg_desc, sizeof(*seg_desc), vcpu, NULL);
}