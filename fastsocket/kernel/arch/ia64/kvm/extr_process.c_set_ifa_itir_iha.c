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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 long IA64_PSR_IC ; 
 long VCPU (struct kvm_vcpu*,long) ; 
 int /*<<< orphan*/  vcpu_get_itir_on_fault (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_set_ifa (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_set_iha (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_set_itir (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_thash (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

void set_ifa_itir_iha(struct kvm_vcpu *vcpu, u64 vadr,
		int set_ifa, int set_itir, int set_iha)
{
	long vpsr;
	u64 value;

	vpsr = VCPU(vcpu, vpsr);
	/* Vol2, Table 8-1 */
	if (vpsr & IA64_PSR_IC) {
		if (set_ifa)
			vcpu_set_ifa(vcpu, vadr);
		if (set_itir) {
			value = vcpu_get_itir_on_fault(vcpu, vadr);
			vcpu_set_itir(vcpu, value);
		}

		if (set_iha) {
			value = vcpu_thash(vcpu, vadr);
			vcpu_set_iha(vcpu, value);
		}
	}
}