#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* sie_block; } ;
struct TYPE_4__ {int /*<<< orphan*/  exit_instr_and_program; } ;
struct kvm_vcpu {TYPE_3__ arch; TYPE_1__ stat; } ;
struct TYPE_5__ {int icptcode; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int handle_instruction (struct kvm_vcpu*) ; 
 int handle_prog (struct kvm_vcpu*) ; 

__attribute__((used)) static int handle_instruction_and_prog(struct kvm_vcpu *vcpu)
{
	int rc, rc2;

	vcpu->stat.exit_instr_and_program++;
	rc = handle_instruction(vcpu);
	rc2 = handle_prog(vcpu);

	if (rc == -ENOTSUPP)
		vcpu->arch.sie_block->icptcode = 0x04;
	if (rc)
		return rc;
	return rc2;
}