#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {TYPE_3__* vpit; } ;
struct kvm {TYPE_4__ arch; } ;
struct TYPE_6__ {TYPE_1__* channels; } ;
struct TYPE_7__ {TYPE_2__ pit_state; } ;
struct TYPE_5__ {int mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  pit_load_count (struct kvm*,int,int /*<<< orphan*/ ) ; 

void kvm_pit_load_count(struct kvm *kvm, int channel, u32 val, int hpet_legacy_start)
{
	u8 saved_mode;
	if (hpet_legacy_start) {
		/* save existing mode for later reenablement */
		saved_mode = kvm->arch.vpit->pit_state.channels[0].mode;
		kvm->arch.vpit->pit_state.channels[0].mode = 0xff; /* disable timer */
		pit_load_count(kvm, channel, val);
		kvm->arch.vpit->pit_state.channels[0].mode = saved_mode;
	} else {
		pit_load_count(kvm, channel, val);
	}
}