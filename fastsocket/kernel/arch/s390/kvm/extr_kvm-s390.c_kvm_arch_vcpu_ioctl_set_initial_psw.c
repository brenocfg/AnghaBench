#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* sie_block; } ;
struct kvm_vcpu {TYPE_3__* run; TYPE_2__ arch; } ;
struct TYPE_9__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  mask; } ;
typedef  TYPE_4__ psw_t ;
struct TYPE_8__ {int /*<<< orphan*/  psw_addr; int /*<<< orphan*/  psw_mask; } ;
struct TYPE_6__ {int /*<<< orphan*/  cpuflags; } ;

/* Variables and functions */
 int CPUSTAT_RUNNING ; 
 int EBUSY ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 

__attribute__((used)) static int kvm_arch_vcpu_ioctl_set_initial_psw(struct kvm_vcpu *vcpu, psw_t psw)
{
	int rc = 0;

	vcpu_load(vcpu);
	if (atomic_read(&vcpu->arch.sie_block->cpuflags) & CPUSTAT_RUNNING)
		rc = -EBUSY;
	else {
		vcpu->run->psw_mask = psw.mask;
		vcpu->run->psw_addr = psw.addr;
	}
	vcpu_put(vcpu);
	return rc;
}