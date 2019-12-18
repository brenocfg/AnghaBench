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
struct TYPE_4__ {int /*<<< orphan*/  r2; } ;
struct TYPE_5__ {TYPE_1__ M45; } ;
typedef  TYPE_2__ INST64 ;

/* Variables and functions */
 unsigned long vcpu_get_gr (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 unsigned long vcpu_get_ifa (struct kvm_vcpu*) ; 
 unsigned long vcpu_get_itir (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_itc_d (struct kvm_vcpu*,unsigned long,unsigned long,unsigned long) ; 

void kvm_itc_d(struct kvm_vcpu *vcpu, INST64 inst)
{
	unsigned long itir, ifa, pte;

	itir = vcpu_get_itir(vcpu);
	ifa = vcpu_get_ifa(vcpu);
	pte = vcpu_get_gr(vcpu, inst.M45.r2);
	vcpu_itc_d(vcpu, pte, itir, ifa);
}