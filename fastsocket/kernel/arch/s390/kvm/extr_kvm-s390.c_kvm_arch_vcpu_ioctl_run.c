#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  exit_userspace; } ;
struct TYPE_15__ {TYPE_6__* sie_block; } ;
struct kvm_vcpu {size_t vcpu_id; TYPE_8__ stat; scalar_t__ sigset_active; TYPE_7__ arch; TYPE_3__* kvm; int /*<<< orphan*/  sigset; scalar_t__ requests; } ;
struct TYPE_12__ {int /*<<< orphan*/  ipb; int /*<<< orphan*/  ipa; int /*<<< orphan*/  icptcode; } ;
struct kvm_run {int exit_reason; int /*<<< orphan*/  psw_addr; int /*<<< orphan*/  psw_mask; TYPE_4__ s390_sieic; } ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_13__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  mask; } ;
struct TYPE_14__ {TYPE_5__ gpsw; int /*<<< orphan*/  ipb; int /*<<< orphan*/  ipa; int /*<<< orphan*/  icptcode; int /*<<< orphan*/  cpuflags; int /*<<< orphan*/  gmslm; } ;
struct TYPE_9__ {int /*<<< orphan*/ ** local_int; } ;
struct TYPE_10__ {TYPE_1__ float_int; } ;
struct TYPE_11__ {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPUSTAT_RUNNING ; 
 int EINTR ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 int EREMOTE ; 
#define  KVM_EXIT_INTR 131 
#define  KVM_EXIT_S390_RESET 130 
#define  KVM_EXIT_S390_SIEIC 129 
#define  KVM_EXIT_UNKNOWN 128 
 int /*<<< orphan*/  KVM_REQ_MMU_RELOAD ; 
 int SIE_INTERCEPT_RERUNVCPU ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  VCPU_EVENT (struct kvm_vcpu*,int,char*,char*) ; 
 int /*<<< orphan*/  __vcpu_run (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  atomic_set_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int kvm_handle_sie_intercept (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_s390_vcpu_set_mem (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  might_fault () ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 

int kvm_arch_vcpu_ioctl_run(struct kvm_vcpu *vcpu, struct kvm_run *kvm_run)
{
	int rc;
	sigset_t sigsaved;

	vcpu_load(vcpu);

rerun_vcpu:
	if (vcpu->requests)
		if (test_and_clear_bit(KVM_REQ_MMU_RELOAD, &vcpu->requests))
			kvm_s390_vcpu_set_mem(vcpu);

	/* verify, that memory has been registered */
	if (!vcpu->arch.sie_block->gmslm) {
		vcpu_put(vcpu);
		VCPU_EVENT(vcpu, 3, "%s", "no memory registered to run vcpu");
		return -EINVAL;
	}

	if (vcpu->sigset_active)
		sigprocmask(SIG_SETMASK, &vcpu->sigset, &sigsaved);

	atomic_set_mask(CPUSTAT_RUNNING, &vcpu->arch.sie_block->cpuflags);

	BUG_ON(vcpu->kvm->arch.float_int.local_int[vcpu->vcpu_id] == NULL);

	switch (kvm_run->exit_reason) {
	case KVM_EXIT_S390_SIEIC:
	case KVM_EXIT_UNKNOWN:
	case KVM_EXIT_INTR:
	case KVM_EXIT_S390_RESET:
		break;
	default:
		BUG();
	}

	vcpu->arch.sie_block->gpsw.mask = kvm_run->psw_mask;
	vcpu->arch.sie_block->gpsw.addr = kvm_run->psw_addr;

	might_fault();

	do {
		__vcpu_run(vcpu);
		rc = kvm_handle_sie_intercept(vcpu);
	} while (!signal_pending(current) && !rc);

	if (rc == SIE_INTERCEPT_RERUNVCPU)
		goto rerun_vcpu;

	if (signal_pending(current) && !rc) {
		kvm_run->exit_reason = KVM_EXIT_INTR;
		rc = -EINTR;
	}

	if (rc == -ENOTSUPP) {
		/* intercept cannot be handled in-kernel, prepare kvm-run */
		kvm_run->exit_reason         = KVM_EXIT_S390_SIEIC;
		kvm_run->s390_sieic.icptcode = vcpu->arch.sie_block->icptcode;
		kvm_run->s390_sieic.ipa      = vcpu->arch.sie_block->ipa;
		kvm_run->s390_sieic.ipb      = vcpu->arch.sie_block->ipb;
		rc = 0;
	}

	if (rc == -EREMOTE) {
		/* intercept was handled, but userspace support is needed
		 * kvm_run has been prepared by the handler */
		rc = 0;
	}

	kvm_run->psw_mask     = vcpu->arch.sie_block->gpsw.mask;
	kvm_run->psw_addr     = vcpu->arch.sie_block->gpsw.addr;

	if (vcpu->sigset_active)
		sigprocmask(SIG_SETMASK, &sigsaved, NULL);

	vcpu_put(vcpu);

	vcpu->stat.exit_userspace++;
	return rc;
}