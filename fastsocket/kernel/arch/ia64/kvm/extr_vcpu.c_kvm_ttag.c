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
struct TYPE_4__ {int /*<<< orphan*/  r1; int /*<<< orphan*/  r3; } ;
struct TYPE_5__ {TYPE_1__ M46; } ;
typedef  TYPE_2__ INST64 ;

/* Variables and functions */
 unsigned long vcpu_get_gr (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_set_gr (struct kvm_vcpu*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long vcpu_ttag (struct kvm_vcpu*,unsigned long) ; 

void kvm_ttag(struct kvm_vcpu *vcpu, INST64 inst)
{
	unsigned long tag, vadr;

	vadr = vcpu_get_gr(vcpu, inst.M46.r3);
	tag = vcpu_ttag(vcpu, vadr);
	vcpu_set_gr(vcpu, inst.M46.r1, tag, 0);
}