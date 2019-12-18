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
struct perf_kvm_stat {int /*<<< orphan*/ * kvm_events_cache; } ;

/* Variables and functions */
 unsigned int EVENTS_CACHE_SIZE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_kvm_event_record(struct perf_kvm_stat *kvm)
{
	unsigned int i;

	for (i = 0; i < EVENTS_CACHE_SIZE; i++)
		INIT_LIST_HEAD(&kvm->kvm_events_cache[i]);
}