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
struct kvm_event_stats {int /*<<< orphan*/  stats; } ;
struct kvm_event {struct kvm_event_stats* vcpu; struct kvm_event_stats total; } ;

/* Variables and functions */
 int /*<<< orphan*/  avg_stats (int /*<<< orphan*/ *) ; 
 double rel_stddev_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stddev_stats (int /*<<< orphan*/ *) ; 

__attribute__((used)) static double kvm_event_rel_stddev(int vcpu_id, struct kvm_event *event)
{
	struct kvm_event_stats *kvm_stats = &event->total;

	if (vcpu_id != -1)
		kvm_stats = &event->vcpu[vcpu_id];

	return rel_stddev_stats(stddev_stats(&kvm_stats->stats),
				avg_stats(&kvm_stats->stats));
}