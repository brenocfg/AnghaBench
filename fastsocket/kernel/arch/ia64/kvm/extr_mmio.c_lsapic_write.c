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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIB_LOW_HALF (unsigned long) ; 
#define  PIB_OFST_INTA 129 
#define  PIB_OFST_XTP 128 
 int PIB_SIZE ; 
 int /*<<< orphan*/  panic_vm (struct kvm_vcpu*,char*,...) ; 
 int /*<<< orphan*/  vlsapic_write_ipi (struct kvm_vcpu*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  vlsapic_write_xtp (struct kvm_vcpu*,unsigned long) ; 

void lsapic_write(struct kvm_vcpu *v, unsigned long addr,
			unsigned long length, unsigned long val)
{
	addr &= (PIB_SIZE - 1);

	switch (addr) {
	case PIB_OFST_INTA:
		panic_vm(v, "Undefined write on PIB INTA\n");
		break;
	case PIB_OFST_XTP:
		if (length == 1) {
			vlsapic_write_xtp(v, val);
		} else {
			panic_vm(v, "Undefined write on PIB XTP\n");
		}
		break;
	default:
		if (PIB_LOW_HALF(addr)) {
			/*Lower half */
			if (length != 8)
				panic_vm(v, "Can't LHF write with size %ld!\n",
						length);
			else
				vlsapic_write_ipi(v, addr, val);
		} else {   /*Upper half */
			panic_vm(v, "IPI-UHF write %lx\n", addr);
		}
		break;
	}
}