#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int size; int count; int cur_count; unsigned int port; int in; scalar_t__ rep; scalar_t__ down; scalar_t__ string; } ;
struct TYPE_8__ {int /*<<< orphan*/  pio_data; TYPE_3__ pio; } ;
struct kvm_vcpu {TYPE_4__ arch; TYPE_2__* run; } ;
struct TYPE_5__ {int size; int data_offset; int count; unsigned int port; int /*<<< orphan*/  direction; } ;
struct TYPE_6__ {TYPE_1__ io; int /*<<< orphan*/  exit_reason; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_EXIT_IO ; 
 int /*<<< orphan*/  KVM_EXIT_IO_IN ; 
 int /*<<< orphan*/  KVM_EXIT_IO_OUT ; 
 int KVM_PIO_PAGE_OFFSET ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  VCPU_REGS_RAX ; 
 int /*<<< orphan*/  complete_pio (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kernel_pio (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 unsigned long kvm_register_read (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned long*,int) ; 
 int /*<<< orphan*/  trace_kvm_pio (int,unsigned int,int,int) ; 

int kvm_emulate_pio(struct kvm_vcpu *vcpu, int in, int size, unsigned port)
{
	unsigned long val;

	trace_kvm_pio(!in, port, size, 1);

	vcpu->run->exit_reason = KVM_EXIT_IO;
	vcpu->run->io.direction = in ? KVM_EXIT_IO_IN : KVM_EXIT_IO_OUT;
	vcpu->run->io.size = vcpu->arch.pio.size = size;
	vcpu->run->io.data_offset = KVM_PIO_PAGE_OFFSET * PAGE_SIZE;
	vcpu->run->io.count = vcpu->arch.pio.count = vcpu->arch.pio.cur_count = 1;
	vcpu->run->io.port = vcpu->arch.pio.port = port;
	vcpu->arch.pio.in = in;
	vcpu->arch.pio.string = 0;
	vcpu->arch.pio.down = 0;
	vcpu->arch.pio.rep = 0;

	val = kvm_register_read(vcpu, VCPU_REGS_RAX);
	memcpy(vcpu->arch.pio_data, &val, 4);

	if (!kernel_pio(vcpu, vcpu->arch.pio_data)) {
		complete_pio(vcpu);
		return 1;
	}
	return 0;
}