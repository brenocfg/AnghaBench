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
typedef  int u8 ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_4__ {scalar_t__ msr_val; } ;
struct TYPE_5__ {TYPE_1__ pv_eoi; } ;
struct TYPE_6__ {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  apic_debug (char*,unsigned long long) ; 
 scalar_t__ pv_eoi_get_user (struct kvm_vcpu*,int*) ; 
 TYPE_3__* vcpi ; 

__attribute__((used)) static bool pv_eoi_get_pending(struct kvm_vcpu *vcpu)
{
	u8 val;
	if (pv_eoi_get_user(vcpu, &val) < 0)
		apic_debug("Can't read EOI MSR value: 0x%llx\n",
			   (unsigned long long)vcpi->arch.pv_eoi.msr_val);
	return val & 0x1;
}