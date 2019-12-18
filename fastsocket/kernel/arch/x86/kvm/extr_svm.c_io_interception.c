#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int /*<<< orphan*/  io_exits; } ;
struct TYPE_10__ {TYPE_1__ stat; } ;
struct vcpu_svm {TYPE_4__ vcpu; TYPE_3__* vmcb; int /*<<< orphan*/  next_rip; } ;
struct TYPE_8__ {int exit_info_1; int /*<<< orphan*/  exit_info_2; } ;
struct TYPE_9__ {TYPE_2__ control; } ;

/* Variables and functions */
 scalar_t__ EMULATE_DO_MMIO ; 
 int SVM_IOIO_SIZE_MASK ; 
 int SVM_IOIO_SIZE_SHIFT ; 
 int SVM_IOIO_STR_MASK ; 
 int SVM_IOIO_TYPE_MASK ; 
 scalar_t__ emulate_instruction (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int kvm_emulate_pio (TYPE_4__*,int,int,unsigned int) ; 
 int /*<<< orphan*/  skip_emulated_instruction (TYPE_4__*) ; 

__attribute__((used)) static int io_interception(struct vcpu_svm *svm)
{
	u32 io_info = svm->vmcb->control.exit_info_1; /* address size bug? */
	int size, in, string;
	unsigned port;

	++svm->vcpu.stat.io_exits;

	svm->next_rip = svm->vmcb->control.exit_info_2;

	string = (io_info & SVM_IOIO_STR_MASK) != 0;

	if (string) {
		if (emulate_instruction(&svm->vcpu, 0) == EMULATE_DO_MMIO)
			return 0;
		return 1;
	}

	in = (io_info & SVM_IOIO_TYPE_MASK) != 0;
	port = io_info >> 16;
	size = (io_info & SVM_IOIO_SIZE_MASK) >> SVM_IOIO_SIZE_SHIFT;

	skip_emulated_instruction(&svm->vcpu);
	return kvm_emulate_pio(&svm->vcpu, in, size, port);
}