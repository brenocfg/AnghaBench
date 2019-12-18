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
typedef  scalar_t__ u64 ;
struct kvm_event_stats {int /*<<< orphan*/  stats; int /*<<< orphan*/  time; } ;

/* Variables and functions */
 int /*<<< orphan*/  update_stats (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
kvm_update_event_stats(struct kvm_event_stats *kvm_stats, u64 time_diff)
{
	kvm_stats->time += time_diff;
	update_stats(&kvm_stats->stats, time_diff);
}