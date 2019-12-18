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
struct TYPE_4__ {unsigned long r1; int cr3; } ;
struct TYPE_5__ {TYPE_1__ M33; } ;
typedef  TYPE_2__ INST64 ;

/* Variables and functions */
 unsigned long VCPU (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 unsigned long vcpu_get_ivr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_set_gr (struct kvm_vcpu*,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vcr ; 

unsigned long kvm_mov_from_cr(struct kvm_vcpu *vcpu, INST64 inst)
{
	unsigned long tgt = inst.M33.r1;
	unsigned long val;

	switch (inst.M33.cr3) {
	case 65:
		val = vcpu_get_ivr(vcpu);
		vcpu_set_gr(vcpu, tgt, val, 0);
		break;

	case 67:
		vcpu_set_gr(vcpu, tgt, 0L, 0);
		break;
	default:
		val = VCPU(vcpu, vcr[inst.M33.cr3]);
		vcpu_set_gr(vcpu, tgt, val, 0);
		break;
	}

	return 0;
}