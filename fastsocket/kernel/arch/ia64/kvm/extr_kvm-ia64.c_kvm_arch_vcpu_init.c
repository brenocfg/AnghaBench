#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
union context {unsigned long* gr; int psr; int* ar; int pr; int* cr; int* rr; unsigned long* br; scalar_t__ caller_unat; } ;
struct vpd {int dummy; } ;
struct thash_data {int dummy; } ;
struct kvm_vcpu_data {int dummy; } ;
struct TYPE_8__ {struct thash_data* hash; } ;
struct TYPE_10__ {struct thash_data* hash; } ;
struct TYPE_14__ {int /*<<< orphan*/  function; } ;
struct TYPE_11__ {long itc_offset; int last_run_cpu; TYPE_1__ vtlb; TYPE_3__ vhpt; int /*<<< orphan*/  dirty_log_lock_pa; int /*<<< orphan*/  __gp; int /*<<< orphan*/  vsa_base; struct vpd* vpd; TYPE_7__ hlt_timer; int /*<<< orphan*/  metaphysical_rr4; int /*<<< orphan*/  metaphysical_rr0; int /*<<< orphan*/  vmm_rr; TYPE_5__* apic; int /*<<< orphan*/  mp_state; scalar_t__ last_itc; union context guest; } ;
struct kvm_vcpu {int /*<<< orphan*/  vcpu_id; TYPE_4__ arch; struct kvm* kvm; } ;
struct kvm_pt_regs {int /*<<< orphan*/  cr_iip; } ;
struct kvm_lapic {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  dirty_log_lock; int /*<<< orphan*/  metaphysical_rr4; int /*<<< orphan*/  metaphysical_rr0; int /*<<< orphan*/  vmm_init_rr; } ;
struct kvm {TYPE_2__ arch; } ;
struct TYPE_13__ {scalar_t__ vmm_entry; scalar_t__ vmm_ivt; } ;
struct TYPE_12__ {struct kvm_vcpu* vcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int ENOMEM ; 
 int FPSR_DEFAULT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 scalar_t__ IS_ERR (struct kvm_vcpu*) ; 
 int KVM_MAX_VCPUS ; 
 int /*<<< orphan*/  KVM_MP_STATE_RUNNABLE ; 
 int /*<<< orphan*/  KVM_MP_STATE_UNINITIALIZED ; 
 int KVM_STK_OFFSET ; 
 int /*<<< orphan*/  PALE_RESET_ENTRY ; 
 int PTR_ERR (struct kvm_vcpu*) ; 
 scalar_t__ VHPT_BASE (int /*<<< orphan*/ ) ; 
 scalar_t__ VPD_BASE (int /*<<< orphan*/ ) ; 
 scalar_t__ VTLB_BASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlt_timer_fn ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_ptce_info (struct kvm_vcpu*) ; 
 unsigned long kvm_get_itc (struct kvm_vcpu*) ; 
 scalar_t__ kvm_vcpu_is_bsp (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vmm_gp ; 
 TYPE_6__* kvm_vmm_info ; 
 int /*<<< orphan*/  kvm_vsa_base ; 
 TYPE_5__* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct kvm_vcpu* to_guest (struct kvm*,struct kvm_vcpu*) ; 
 struct kvm_pt_regs* vcpu_regs (struct kvm_vcpu*) ; 

int kvm_arch_vcpu_init(struct kvm_vcpu *vcpu)
{
	struct kvm_vcpu *v;
	int r;
	int i;
	long itc_offset;
	struct kvm *kvm = vcpu->kvm;
	struct kvm_pt_regs *regs = vcpu_regs(vcpu);

	union context *p_ctx = &vcpu->arch.guest;
	struct kvm_vcpu *vmm_vcpu = to_guest(vcpu->kvm, vcpu);

	/*Init vcpu context for first run.*/
	if (IS_ERR(vmm_vcpu))
		return PTR_ERR(vmm_vcpu);

	if (kvm_vcpu_is_bsp(vcpu)) {
		vcpu->arch.mp_state = KVM_MP_STATE_RUNNABLE;

		/*Set entry address for first run.*/
		regs->cr_iip = PALE_RESET_ENTRY;

		/*Initialize itc offset for vcpus*/
		itc_offset = 0UL - kvm_get_itc(vcpu);
		for (i = 0; i < KVM_MAX_VCPUS; i++) {
			v = (struct kvm_vcpu *)((char *)vcpu +
					sizeof(struct kvm_vcpu_data) * i);
			v->arch.itc_offset = itc_offset;
			v->arch.last_itc = 0;
		}
	} else
		vcpu->arch.mp_state = KVM_MP_STATE_UNINITIALIZED;

	r = -ENOMEM;
	vcpu->arch.apic = kzalloc(sizeof(struct kvm_lapic), GFP_KERNEL);
	if (!vcpu->arch.apic)
		goto out;
	vcpu->arch.apic->vcpu = vcpu;

	p_ctx->gr[1] = 0;
	p_ctx->gr[12] = (unsigned long)((char *)vmm_vcpu + KVM_STK_OFFSET);
	p_ctx->gr[13] = (unsigned long)vmm_vcpu;
	p_ctx->psr = 0x1008522000UL;
	p_ctx->ar[40] = FPSR_DEFAULT; /*fpsr*/
	p_ctx->caller_unat = 0;
	p_ctx->pr = 0x0;
	p_ctx->ar[36] = 0x0; /*unat*/
	p_ctx->ar[19] = 0x0; /*rnat*/
	p_ctx->ar[18] = (unsigned long)vmm_vcpu +
				((sizeof(struct kvm_vcpu)+15) & ~15);
	p_ctx->ar[64] = 0x0; /*pfs*/
	p_ctx->cr[0] = 0x7e04UL;
	p_ctx->cr[2] = (unsigned long)kvm_vmm_info->vmm_ivt;
	p_ctx->cr[8] = 0x3c;

	/*Initilize region register*/
	p_ctx->rr[0] = 0x30;
	p_ctx->rr[1] = 0x30;
	p_ctx->rr[2] = 0x30;
	p_ctx->rr[3] = 0x30;
	p_ctx->rr[4] = 0x30;
	p_ctx->rr[5] = 0x30;
	p_ctx->rr[7] = 0x30;

	/*Initilize branch register 0*/
	p_ctx->br[0] = *(unsigned long *)kvm_vmm_info->vmm_entry;

	vcpu->arch.vmm_rr = kvm->arch.vmm_init_rr;
	vcpu->arch.metaphysical_rr0 = kvm->arch.metaphysical_rr0;
	vcpu->arch.metaphysical_rr4 = kvm->arch.metaphysical_rr4;

	hrtimer_init(&vcpu->arch.hlt_timer, CLOCK_MONOTONIC, HRTIMER_MODE_ABS);
	vcpu->arch.hlt_timer.function = hlt_timer_fn;

	vcpu->arch.last_run_cpu = -1;
	vcpu->arch.vpd = (struct vpd *)VPD_BASE(vcpu->vcpu_id);
	vcpu->arch.vsa_base = kvm_vsa_base;
	vcpu->arch.__gp = kvm_vmm_gp;
	vcpu->arch.dirty_log_lock_pa = __pa(&kvm->arch.dirty_log_lock);
	vcpu->arch.vhpt.hash = (struct thash_data *)VHPT_BASE(vcpu->vcpu_id);
	vcpu->arch.vtlb.hash = (struct thash_data *)VTLB_BASE(vcpu->vcpu_id);
	init_ptce_info(vcpu);

	r = 0;
out:
	return r;
}