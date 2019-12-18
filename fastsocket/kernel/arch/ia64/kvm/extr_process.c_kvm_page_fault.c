#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
union ia64_pta {void* val; } ;
union ia64_isr {int ni; int /*<<< orphan*/  val; scalar_t__ rs; scalar_t__ sp; } ;
typedef  int u64 ;
struct thash_data {unsigned long ps; int ppn; int pl; int ma; int /*<<< orphan*/  itir; int /*<<< orphan*/  page_flags; } ;
struct kvm_vcpu {int dummy; } ;
struct kvm_pt_regs {int cr_ipsr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_REF ; 
 int D_TLB ; 
 int IA64_PSR_CPL0_BIT ; 
 unsigned long IA64_PSR_IC ; 
 int /*<<< orphan*/  INST_REF ; 
 int I_TLB ; 
 int PAGE_SHIFT ; 
 int RR_PS_MASK ; 
 int RR_RID_MASK ; 
 int /*<<< orphan*/  RSE_REF ; 
 unsigned long VCPU (struct kvm_vcpu*,unsigned long) ; 
 int /*<<< orphan*/  VMX (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int _PAGE_MA_MASK ; 
 int _PAGE_MA_ST ; 
 int _PAGE_P ; 
 scalar_t__ __gpfn_is_io (int) ; 
 int /*<<< orphan*/  alt_dtlb (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  alt_itlb (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  cr_isr ; 
 struct kvm_vcpu* current_vcpu ; 
 int /*<<< orphan*/  data_access_rights (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  dtlb_fault (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  dvhpt_fault (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  emulate_io_inst (struct kvm_vcpu*,int,int) ; 
 int /*<<< orphan*/  guest_vhpt_lookup (int,int*) ; 
 int /*<<< orphan*/  handle_lds (struct kvm_pt_regs*) ; 
 int /*<<< orphan*/  inst_page_not_present (struct kvm_vcpu*,int) ; 
 scalar_t__ is_physical_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  itlb_fault (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  ivhpt_fault (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  nested_dtlb (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  physical_tlb_miss (struct kvm_vcpu*,int,int) ; 
 int /*<<< orphan*/  thash_purge_and_insert (struct kvm_vcpu*,int,int,int,int) ; 
 int /*<<< orphan*/  thash_vhpt_insert (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 void* vcpu_get_pta (struct kvm_vcpu*) ; 
 int vcpu_get_rr (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  vcpu_set_isr (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int vcpu_thash (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  vhpt_enabled (struct kvm_vcpu*,int,int /*<<< orphan*/ ) ; 
 struct thash_data* vtlb_lookup (struct kvm_vcpu*,int,int) ; 

void kvm_page_fault(u64 vadr , u64 vec, struct kvm_pt_regs *regs)
{
	unsigned long vpsr;
	int type;

	u64 vhpt_adr, gppa, pteval, rr, itir;
	union ia64_isr misr;
	union ia64_pta vpta;
	struct thash_data *data;
	struct kvm_vcpu *v = current_vcpu;

	vpsr = VCPU(v, vpsr);
	misr.val = VMX(v, cr_isr);

	type = vec;

	if (is_physical_mode(v) && (!(vadr << 1 >> 62))) {
		if (vec == 2) {
			if (__gpfn_is_io((vadr << 1) >> (PAGE_SHIFT + 1))) {
				emulate_io_inst(v, ((vadr << 1) >> 1), 4);
				return;
			}
		}
		physical_tlb_miss(v, vadr, type);
		return;
	}
	data = vtlb_lookup(v, vadr, type);
	if (data != 0) {
		if (type == D_TLB) {
			gppa = (vadr & ((1UL << data->ps) - 1))
				+ (data->ppn >> (data->ps - 12) << data->ps);
			if (__gpfn_is_io(gppa >> PAGE_SHIFT)) {
				if (data->pl >= ((regs->cr_ipsr >>
						IA64_PSR_CPL0_BIT) & 3))
					emulate_io_inst(v, gppa, data->ma);
				else {
					vcpu_set_isr(v, misr.val);
					data_access_rights(v, vadr);
				}
				return ;
			}
		}
		thash_vhpt_insert(v, data->page_flags, data->itir, vadr, type);

	} else if (type == D_TLB) {
		if (misr.sp) {
			handle_lds(regs);
			return;
		}

		rr = vcpu_get_rr(v, vadr);
		itir = rr & (RR_RID_MASK | RR_PS_MASK);

		if (!vhpt_enabled(v, vadr, misr.rs ? RSE_REF : DATA_REF)) {
			if (vpsr & IA64_PSR_IC) {
				vcpu_set_isr(v, misr.val);
				alt_dtlb(v, vadr);
			} else {
				nested_dtlb(v);
			}
			return ;
		}

		vpta.val = vcpu_get_pta(v);
		/* avoid recursively walking (short format) VHPT */

		vhpt_adr = vcpu_thash(v, vadr);
		if (!guest_vhpt_lookup(vhpt_adr, &pteval)) {
			/* VHPT successfully read.  */
			if (!(pteval & _PAGE_P)) {
				if (vpsr & IA64_PSR_IC) {
					vcpu_set_isr(v, misr.val);
					dtlb_fault(v, vadr);
				} else {
					nested_dtlb(v);
				}
			} else if ((pteval & _PAGE_MA_MASK) != _PAGE_MA_ST) {
				thash_purge_and_insert(v, pteval, itir,
								vadr, D_TLB);
			} else if (vpsr & IA64_PSR_IC) {
				vcpu_set_isr(v, misr.val);
				dtlb_fault(v, vadr);
			} else {
				nested_dtlb(v);
			}
		} else {
			/* Can't read VHPT.  */
			if (vpsr & IA64_PSR_IC) {
				vcpu_set_isr(v, misr.val);
				dvhpt_fault(v, vadr);
			} else {
				nested_dtlb(v);
			}
		}
	} else if (type == I_TLB) {
		if (!(vpsr & IA64_PSR_IC))
			misr.ni = 1;
		if (!vhpt_enabled(v, vadr, INST_REF)) {
			vcpu_set_isr(v, misr.val);
			alt_itlb(v, vadr);
			return;
		}

		vpta.val = vcpu_get_pta(v);

		vhpt_adr = vcpu_thash(v, vadr);
		if (!guest_vhpt_lookup(vhpt_adr, &pteval)) {
			/* VHPT successfully read.  */
			if (pteval & _PAGE_P) {
				if ((pteval & _PAGE_MA_MASK) == _PAGE_MA_ST) {
					vcpu_set_isr(v, misr.val);
					itlb_fault(v, vadr);
					return ;
				}
				rr = vcpu_get_rr(v, vadr);
				itir = rr & (RR_RID_MASK | RR_PS_MASK);
				thash_purge_and_insert(v, pteval, itir,
							vadr, I_TLB);
			} else {
				vcpu_set_isr(v, misr.val);
				inst_page_not_present(v, vadr);
			}
		} else {
			vcpu_set_isr(v, misr.val);
			ivhpt_fault(v, vadr);
		}
	}
}