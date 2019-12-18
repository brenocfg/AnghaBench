#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int size; unsigned long count; unsigned long cur_count; unsigned int port; int in; int string; int down; int rep; int /*<<< orphan*/  guest_gva; } ;
struct TYPE_9__ {TYPE_3__ pio; } ;
struct kvm_vcpu {TYPE_4__ arch; TYPE_2__* run; } ;
typedef  int /*<<< orphan*/  gva_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* skip_emulated_instruction ) (struct kvm_vcpu*) ;} ;
struct TYPE_6__ {int size; int data_offset; unsigned long count; unsigned int port; int /*<<< orphan*/  direction; } ;
struct TYPE_7__ {TYPE_1__ io; int /*<<< orphan*/  exit_reason; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_EXIT_IO ; 
 int /*<<< orphan*/  KVM_EXIT_IO_IN ; 
 int /*<<< orphan*/  KVM_EXIT_IO_OUT ; 
 int KVM_PIO_PAGE_OFFSET ; 
 int PAGE_SIZE ; 
 int X86EMUL_PROPAGATE_FAULT ; 
 int /*<<< orphan*/  complete_pio (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_inject_gp (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 TYPE_5__* kvm_x86_ops ; 
 unsigned int min (unsigned long,unsigned long) ; 
 int offset_in_page (int /*<<< orphan*/ ) ; 
 int pio_copy_data (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  pio_string_write (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  pr_unimpl (struct kvm_vcpu*,char*) ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub2 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_pio (int,unsigned int,int,unsigned long) ; 

int kvm_emulate_pio_string(struct kvm_vcpu *vcpu, int in,
		  int size, unsigned long count, int down,
		  gva_t address, int rep, unsigned port)
{
	unsigned now, in_page;
	int ret = 0;

	trace_kvm_pio(!in, port, size, count);

	vcpu->run->exit_reason = KVM_EXIT_IO;
	vcpu->run->io.direction = in ? KVM_EXIT_IO_IN : KVM_EXIT_IO_OUT;
	vcpu->run->io.size = vcpu->arch.pio.size = size;
	vcpu->run->io.data_offset = KVM_PIO_PAGE_OFFSET * PAGE_SIZE;
	vcpu->run->io.count = vcpu->arch.pio.count = vcpu->arch.pio.cur_count = count;
	vcpu->run->io.port = vcpu->arch.pio.port = port;
	vcpu->arch.pio.in = in;
	vcpu->arch.pio.string = 1;
	vcpu->arch.pio.down = down;
	vcpu->arch.pio.rep = rep;

	if (!count) {
		kvm_x86_ops->skip_emulated_instruction(vcpu);
		return 1;
	}

	if (!down)
		in_page = PAGE_SIZE - offset_in_page(address);
	else
		in_page = offset_in_page(address) + size;
	now = min(count, (unsigned long)in_page / size);
	if (!now)
		now = 1;
	if (down) {
		/*
		 * String I/O in reverse.  Yuck.  Kill the guest, fix later.
		 */
		pr_unimpl(vcpu, "guest string pio down\n");
		kvm_inject_gp(vcpu, 0);
		return 1;
	}
	vcpu->run->io.count = now;
	vcpu->arch.pio.cur_count = now;

	if (vcpu->arch.pio.cur_count == vcpu->arch.pio.count)
		kvm_x86_ops->skip_emulated_instruction(vcpu);

	vcpu->arch.pio.guest_gva = address;

	if (!vcpu->arch.pio.in) {
		/* string PIO write */
		ret = pio_copy_data(vcpu);
		if (ret == X86EMUL_PROPAGATE_FAULT)
			return 1;
		if (ret == 0 && !pio_string_write(vcpu)) {
			complete_pio(vcpu);
			if (vcpu->arch.pio.count == 0)
				ret = 1;
		}
	}
	/* no string PIO read support yet */

	return ret;
}