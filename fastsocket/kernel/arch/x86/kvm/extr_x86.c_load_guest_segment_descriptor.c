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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct kvm_vcpu {int dummy; } ;
struct descriptor_table {int limit; scalar_t__ base; } ;
struct desc_struct {int dummy; } ;
typedef  scalar_t__ gva_t ;

/* Variables and functions */
 int /*<<< orphan*/  GP_VECTOR ; 
 int X86EMUL_PROPAGATE_FAULT ; 
 int /*<<< orphan*/  get_segment_descriptor_dtable (struct kvm_vcpu*,int,struct descriptor_table*) ; 
 int /*<<< orphan*/  kvm_inject_page_fault (struct kvm_vcpu*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_queue_exception_e (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ; 
 int kvm_read_guest_virt_system (scalar_t__,struct desc_struct*,int,struct kvm_vcpu*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int load_guest_segment_descriptor(struct kvm_vcpu *vcpu, u16 selector,
					 struct desc_struct *seg_desc)
{
	struct descriptor_table dtable;
	u16 index = selector >> 3;
	int ret;
	u32 err;
	gva_t addr;

	get_segment_descriptor_dtable(vcpu, selector, &dtable);

	if (dtable.limit < index * 8 + 7) {
		kvm_queue_exception_e(vcpu, GP_VECTOR, selector & 0xfffc);
		return 1;
	}
	addr = dtable.base + index * 8;
	ret = kvm_read_guest_virt_system(addr, seg_desc, sizeof(*seg_desc),
					 vcpu,  &err);
	if (ret == X86EMUL_PROPAGATE_FAULT)
		kvm_inject_page_fault(vcpu, addr, err);

       return ret;
}