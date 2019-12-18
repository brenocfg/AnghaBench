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
struct vcpu_event_record {int /*<<< orphan*/  start_time; struct kvm_event* last_event; } ;
struct perf_kvm_stat {int dummy; } ;
struct kvm_event {int dummy; } ;
struct event_key {scalar_t__ key; } ;

/* Variables and functions */
 scalar_t__ INVALID_KEY ; 
 struct kvm_event* find_create_kvm_event (struct perf_kvm_stat*,struct event_key*) ; 

__attribute__((used)) static bool handle_begin_event(struct perf_kvm_stat *kvm,
			       struct vcpu_event_record *vcpu_record,
			       struct event_key *key, u64 timestamp)
{
	struct kvm_event *event = NULL;

	if (key->key != INVALID_KEY)
		event = find_create_kvm_event(kvm, key);

	vcpu_record->last_event = event;
	vcpu_record->start_time = timestamp;
	return true;
}