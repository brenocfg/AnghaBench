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
struct TYPE_2__ {int /*<<< orphan*/  regs_dirty; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_REGS_RAX ; 
 int /*<<< orphan*/  VCPU_REGS_RIP ; 
 int /*<<< orphan*/  VCPU_REGS_RSP ; 
 int /*<<< orphan*/  kvm_register_read (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cache_all_regs(struct kvm_vcpu *vcpu)
{
	kvm_register_read(vcpu, VCPU_REGS_RAX);
	kvm_register_read(vcpu, VCPU_REGS_RSP);
	kvm_register_read(vcpu, VCPU_REGS_RIP);
	vcpu->arch.regs_dirty = ~0;
}