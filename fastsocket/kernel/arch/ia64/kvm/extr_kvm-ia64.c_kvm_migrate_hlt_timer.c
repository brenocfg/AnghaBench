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
struct hrtimer {int dummy; } ;
struct TYPE_2__ {struct hrtimer hlt_timer; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 scalar_t__ hrtimer_cancel (struct hrtimer*) ; 
 int /*<<< orphan*/  hrtimer_start_expires (struct hrtimer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_migrate_hlt_timer(struct kvm_vcpu *vcpu)
{
	struct hrtimer *p_ht = &vcpu->arch.hlt_timer;

	if (hrtimer_cancel(p_ht))
		hrtimer_start_expires(p_ht, HRTIMER_MODE_ABS);
}