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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  tsc_catchup_mult; int /*<<< orphan*/  tsc_catchup_shift; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  kvm_get_time_scale (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kvm_init_tsc_catchup(struct kvm_vcpu *vcpu, u32 this_tsc_khz)
{
	/* Compute a scale to convert nanoseconds in TSC cycles */
	kvm_get_time_scale(this_tsc_khz, NSEC_PER_SEC / 1000,
			   &vcpu->arch.tsc_catchup_shift,
			   &vcpu->arch.tsc_catchup_mult);
}