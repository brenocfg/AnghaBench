#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ virtual_tsc_khz; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 scalar_t__ __get_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_tsc_khz ; 

u64 vcpu_tsc_khz(struct kvm_vcpu *vcpu)
{
	if (vcpu->arch.virtual_tsc_khz)
		return vcpu->arch.virtual_tsc_khz;
	else
		return __get_cpu_var(cpu_tsc_khz);
}