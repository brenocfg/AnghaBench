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
union cpuid3_t {int number; int /*<<< orphan*/  value; } ;
struct TYPE_6__ {int d_vmsw; } ;
struct TYPE_5__ {int a_from_int_cr; int a_to_int_cr; int a_from_psr; int a_from_cpuid; int a_cover; int a_bsw; int a_int; } ;
struct vpd {int /*<<< orphan*/  virt_env_vaddr; TYPE_3__ vdc; TYPE_2__ vac; int /*<<< orphan*/ * vcpuid; } ;
struct TYPE_4__ {int /*<<< orphan*/  vpd; } ;
struct kvm_vcpu {TYPE_1__ arch; int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct vpd*) ; 
 int /*<<< orphan*/  KVM_VM_BUFFER_BASE ; 
 int PTR_ERR (struct vpd*) ; 
 int /*<<< orphan*/  ia64_get_cpuid (int) ; 
 struct vpd* to_host (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vti_init_vpd(struct kvm_vcpu *vcpu)
{
	int i;
	union cpuid3_t cpuid3;
	struct vpd *vpd = to_host(vcpu->kvm, vcpu->arch.vpd);

	if (IS_ERR(vpd))
		return PTR_ERR(vpd);

	/* CPUID init */
	for (i = 0; i < 5; i++)
		vpd->vcpuid[i] = ia64_get_cpuid(i);

	/* Limit the CPUID number to 5 */
	cpuid3.value = vpd->vcpuid[3];
	cpuid3.number = 4;	/* 5 - 1 */
	vpd->vcpuid[3] = cpuid3.value;

	/*Set vac and vdc fields*/
	vpd->vac.a_from_int_cr = 1;
	vpd->vac.a_to_int_cr = 1;
	vpd->vac.a_from_psr = 1;
	vpd->vac.a_from_cpuid = 1;
	vpd->vac.a_cover = 1;
	vpd->vac.a_bsw = 1;
	vpd->vac.a_int = 1;
	vpd->vdc.d_vmsw = 1;

	/*Set virtual buffer*/
	vpd->virt_env_vaddr = KVM_VM_BUFFER_BASE;

	return 0;
}