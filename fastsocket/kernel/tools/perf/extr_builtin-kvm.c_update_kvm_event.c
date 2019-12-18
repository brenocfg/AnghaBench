#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct kvm_event {int /*<<< orphan*/ * vcpu; int /*<<< orphan*/  total; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_event_expand (struct kvm_event*,int) ; 
 int /*<<< orphan*/  kvm_update_event_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool update_kvm_event(struct kvm_event *event, int vcpu_id,
			     u64 time_diff)
{
	if (vcpu_id == -1) {
		kvm_update_event_stats(&event->total, time_diff);
		return true;
	}

	if (!kvm_event_expand(event, vcpu_id))
		return false;

	kvm_update_event_stats(&event->vcpu[vcpu_id], time_diff);
	return true;
}