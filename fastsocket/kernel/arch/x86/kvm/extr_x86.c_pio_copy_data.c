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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {unsigned int size; unsigned int cur_count; scalar_t__ in; int /*<<< orphan*/  guest_gva; } ;
struct TYPE_4__ {TYPE_1__ pio; void* pio_data; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
typedef  int /*<<< orphan*/  gva_t ;

/* Variables and functions */
 int X86EMUL_PROPAGATE_FAULT ; 
 int /*<<< orphan*/  kvm_inject_page_fault (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kvm_read_guest_virt (int /*<<< orphan*/ ,void*,unsigned int,struct kvm_vcpu*,int /*<<< orphan*/ *) ; 
 int kvm_write_guest_virt (int /*<<< orphan*/ ,void*,unsigned int,struct kvm_vcpu*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pio_copy_data(struct kvm_vcpu *vcpu)
{
	void *p = vcpu->arch.pio_data;
	gva_t q = vcpu->arch.pio.guest_gva;
	unsigned bytes;
	int ret;
	u32 error_code;

	bytes = vcpu->arch.pio.size * vcpu->arch.pio.cur_count;
	if (vcpu->arch.pio.in)
		ret = kvm_write_guest_virt(q, p, bytes, vcpu, &error_code);
	else
		ret = kvm_read_guest_virt(q, p, bytes, vcpu, &error_code);

	if (ret == X86EMUL_PROPAGATE_FAULT)
		kvm_inject_page_fault(vcpu, q, error_code);

	return ret;
}