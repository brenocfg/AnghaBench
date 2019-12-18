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
struct kvm_kpit_channel_state {int mode; int count; } ;
struct TYPE_6__ {TYPE_2__* vpit; } ;
struct kvm {TYPE_3__ arch; } ;
typedef  int s64 ;
struct TYPE_4__ {int /*<<< orphan*/  lock; struct kvm_kpit_channel_state* channels; } ;
struct TYPE_5__ {TYPE_1__ pit_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_PIT_FREQ ; 
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int kpit_elapsed (struct kvm*,struct kvm_kpit_channel_state*,int) ; 
 int mod_64 (int,int) ; 
 int muldiv64 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pit_get_count(struct kvm *kvm, int channel)
{
	struct kvm_kpit_channel_state *c =
		&kvm->arch.vpit->pit_state.channels[channel];
	s64 d, t;
	int counter;

	WARN_ON(!mutex_is_locked(&kvm->arch.vpit->pit_state.lock));

	t = kpit_elapsed(kvm, c, channel);
	d = muldiv64(t, KVM_PIT_FREQ, NSEC_PER_SEC);

	switch (c->mode) {
	case 0:
	case 1:
	case 4:
	case 5:
		counter = (c->count - d) & 0xffff;
		break;
	case 3:
		/* XXX: may be incorrect for odd counts */
		counter = c->count - (mod_64((2 * d), c->count));
		break;
	default:
		counter = c->count - mod_64(d, c->count);
		break;
	}
	return counter;
}