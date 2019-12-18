#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kvm_vcpu {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  r2; int /*<<< orphan*/  r3; } ;
struct TYPE_5__ {TYPE_1__ M45; } ;
typedef  TYPE_2__ INST64 ;

/* Variables and functions */
 int /*<<< orphan*/  itir_ps (unsigned long) ; 
 unsigned long vcpu_get_gr (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_ptc_l (struct kvm_vcpu*,unsigned long,int /*<<< orphan*/ ) ; 

void kvm_ptc_l(struct kvm_vcpu *vcpu, INST64 inst)
{
	unsigned long ifa, itir;

	ifa = vcpu_get_gr(vcpu, inst.M45.r3);
	itir = vcpu_get_gr(vcpu, inst.M45.r2);
	vcpu_ptc_l(vcpu, ifa, itir_ps(itir));
}