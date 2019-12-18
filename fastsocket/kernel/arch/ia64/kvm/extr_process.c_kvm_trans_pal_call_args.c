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
struct thash_data {unsigned long page_flags; unsigned long gpaddr; int /*<<< orphan*/  ps; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_TLB ; 
 unsigned long PAGEALIGN (unsigned long,int /*<<< orphan*/ ) ; 
 int PSIZE (int /*<<< orphan*/ ) ; 
 unsigned long _PAGE_PPN_MASK ; 
 scalar_t__ __va (unsigned long) ; 
 int /*<<< orphan*/  is_physical_mode (struct kvm_vcpu*) ; 
 unsigned long kvm_gpa_to_mpa (unsigned long) ; 
 struct thash_data* vhpt_lookup (unsigned long) ; 
 struct thash_data* vtlb_lookup (struct kvm_vcpu*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long kvm_trans_pal_call_args(struct kvm_vcpu *vcpu,
						unsigned long arg)
{
	struct thash_data *data;
	unsigned long gpa, poff;

	if (!is_physical_mode(vcpu)) {
		/* Depends on caller to provide the DTR or DTC mapping.*/
		data = vtlb_lookup(vcpu, arg, D_TLB);
		if (data)
			gpa = data->page_flags & _PAGE_PPN_MASK;
		else {
			data = vhpt_lookup(arg);
			if (!data)
				return 0;
			gpa = data->gpaddr & _PAGE_PPN_MASK;
		}

		poff = arg & (PSIZE(data->ps) - 1);
		arg = PAGEALIGN(gpa, data->ps) | poff;
	}
	arg = kvm_gpa_to_mpa(arg << 1 >> 1);

	return (unsigned long)__va(arg);
}