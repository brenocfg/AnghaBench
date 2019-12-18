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
typedef  int /*<<< orphan*/  u32 ;
struct kvm_kpit_channel_state {int mode; int /*<<< orphan*/  gate; int /*<<< orphan*/  count_load_time; } ;
struct TYPE_6__ {TYPE_2__* vpit; } ;
struct kvm {TYPE_3__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; struct kvm_kpit_channel_state* channels; } ;
struct TYPE_5__ {TYPE_1__ pit_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pit_set_gate(struct kvm *kvm, int channel, u32 val)
{
	struct kvm_kpit_channel_state *c =
		&kvm->arch.vpit->pit_state.channels[channel];

	WARN_ON(!mutex_is_locked(&kvm->arch.vpit->pit_state.lock));

	switch (c->mode) {
	default:
	case 0:
	case 4:
		/* XXX: just disable/enable counting */
		break;
	case 1:
	case 2:
	case 3:
	case 5:
		/* Restart counting on rising edge. */
		if (c->gate < val)
			c->count_load_time = ktime_get();
		break;
	}

	c->gate = val;
}