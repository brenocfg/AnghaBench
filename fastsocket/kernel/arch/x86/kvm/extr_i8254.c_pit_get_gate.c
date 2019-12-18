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
struct TYPE_8__ {TYPE_3__* vpit; } ;
struct kvm {TYPE_4__ arch; } ;
struct TYPE_6__ {TYPE_1__* channels; int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {TYPE_2__ pit_state; } ;
struct TYPE_5__ {int gate; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pit_get_gate(struct kvm *kvm, int channel)
{
	WARN_ON(!mutex_is_locked(&kvm->arch.vpit->pit_state.lock));

	return kvm->arch.vpit->pit_state.channels[channel].gate;
}