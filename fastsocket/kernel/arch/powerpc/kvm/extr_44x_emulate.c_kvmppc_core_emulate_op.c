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
struct TYPE_4__ {int io_gpr; int dcr_needed; int /*<<< orphan*/ * gpr; int /*<<< orphan*/  cpr0_cfgaddr; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {int dcrn; int is_write; int /*<<< orphan*/  data; } ;
struct kvm_run {TYPE_1__ dcr; } ;

/* Variables and functions */
#define  DCRN_CPR0_CONFIG_ADDR 134 
#define  DCRN_CPR0_CONFIG_DATA 133 
 int /*<<< orphan*/  DCR_EXITS ; 
 int EMULATE_DONE ; 
 int EMULATE_DO_DCR ; 
 int EMULATE_FAIL ; 
#define  XOP_ICCCI 132 
#define  XOP_MFDCR 131 
#define  XOP_MTDCR 130 
#define  XOP_TLBSX 129 
#define  XOP_TLBWE 128 
 int get_dcrn (unsigned int) ; 
 int get_op (unsigned int) ; 
 int get_ra (unsigned int) ; 
 int get_rb (unsigned int) ; 
 int get_rc (unsigned int) ; 
 int get_rs (unsigned int) ; 
 int get_rt (unsigned int) ; 
 int get_ws (unsigned int) ; 
 int /*<<< orphan*/  get_xop (unsigned int) ; 
 int kvmppc_44x_emul_tlbsx (struct kvm_vcpu*,int,int,int,int) ; 
 int kvmppc_44x_emul_tlbwe (struct kvm_vcpu*,int,int,int) ; 
 int /*<<< orphan*/  kvmppc_account_exit (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int kvmppc_booke_emulate_op (struct kvm_run*,struct kvm_vcpu*,unsigned int,int*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  mfdcr (int const) ; 
 int /*<<< orphan*/  mtdcr (int const,int /*<<< orphan*/ ) ; 

int kvmppc_core_emulate_op(struct kvm_run *run, struct kvm_vcpu *vcpu,
                           unsigned int inst, int *advance)
{
	int emulated = EMULATE_DONE;
	int dcrn;
	int ra;
	int rb;
	int rc;
	int rs;
	int rt;
	int ws;

	switch (get_op(inst)) {
	case 31:
		switch (get_xop(inst)) {

		case XOP_MFDCR:
			dcrn = get_dcrn(inst);
			rt = get_rt(inst);

			/* The guest may access CPR0 registers to determine the timebase
			 * frequency, and it must know the real host frequency because it
			 * can directly access the timebase registers.
			 *
			 * It would be possible to emulate those accesses in userspace,
			 * but userspace can really only figure out the end frequency.
			 * We could decompose that into the factors that compute it, but
			 * that's tricky math, and it's easier to just report the real
			 * CPR0 values.
			 */
			switch (dcrn) {
			case DCRN_CPR0_CONFIG_ADDR:
				vcpu->arch.gpr[rt] = vcpu->arch.cpr0_cfgaddr;
				break;
			case DCRN_CPR0_CONFIG_DATA:
				local_irq_disable();
				mtdcr(DCRN_CPR0_CONFIG_ADDR,
					  vcpu->arch.cpr0_cfgaddr);
				vcpu->arch.gpr[rt] = mfdcr(DCRN_CPR0_CONFIG_DATA);
				local_irq_enable();
				break;
			default:
				run->dcr.dcrn = dcrn;
				run->dcr.data =  0;
				run->dcr.is_write = 0;
				vcpu->arch.io_gpr = rt;
				vcpu->arch.dcr_needed = 1;
				kvmppc_account_exit(vcpu, DCR_EXITS);
				emulated = EMULATE_DO_DCR;
			}

			break;

		case XOP_MTDCR:
			dcrn = get_dcrn(inst);
			rs = get_rs(inst);

			/* emulate some access in kernel */
			switch (dcrn) {
			case DCRN_CPR0_CONFIG_ADDR:
				vcpu->arch.cpr0_cfgaddr = vcpu->arch.gpr[rs];
				break;
			default:
				run->dcr.dcrn = dcrn;
				run->dcr.data = vcpu->arch.gpr[rs];
				run->dcr.is_write = 1;
				vcpu->arch.dcr_needed = 1;
				kvmppc_account_exit(vcpu, DCR_EXITS);
				emulated = EMULATE_DO_DCR;
			}

			break;

		case XOP_TLBWE:
			ra = get_ra(inst);
			rs = get_rs(inst);
			ws = get_ws(inst);
			emulated = kvmppc_44x_emul_tlbwe(vcpu, ra, rs, ws);
			break;

		case XOP_TLBSX:
			rt = get_rt(inst);
			ra = get_ra(inst);
			rb = get_rb(inst);
			rc = get_rc(inst);
			emulated = kvmppc_44x_emul_tlbsx(vcpu, rt, ra, rb, rc);
			break;

		case XOP_ICCCI:
			break;

		default:
			emulated = EMULATE_FAIL;
		}

		break;

	default:
		emulated = EMULATE_FAIL;
	}

	if (emulated == EMULATE_FAIL)
		emulated = kvmppc_booke_emulate_op(run, vcpu, inst, advance);

	return emulated;
}