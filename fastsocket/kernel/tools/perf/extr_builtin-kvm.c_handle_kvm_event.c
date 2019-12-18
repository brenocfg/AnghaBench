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
struct vcpu_event_record {scalar_t__ vcpu_id; } ;
struct thread {int dummy; } ;
struct perf_sample {int /*<<< orphan*/  time; } ;
struct perf_kvm_stat {int trace_vcpu; TYPE_1__* events_ops; } ;
struct perf_evsel {int dummy; } ;
struct event_key {int /*<<< orphan*/  key; } ;
struct TYPE_2__ {scalar_t__ (* is_end_event ) (struct perf_evsel*,struct perf_sample*,struct event_key*) ;scalar_t__ (* is_begin_event ) (struct perf_evsel*,struct perf_sample*,struct event_key*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_KEY ; 
 int handle_begin_event (struct perf_kvm_stat*,struct vcpu_event_record*,struct event_key*,int /*<<< orphan*/ ) ; 
 int handle_end_event (struct perf_kvm_stat*,struct vcpu_event_record*,struct event_key*,int /*<<< orphan*/ ) ; 
 struct vcpu_event_record* per_vcpu_record (struct thread*,struct perf_evsel*,struct perf_sample*) ; 
 scalar_t__ stub1 (struct perf_evsel*,struct perf_sample*,struct event_key*) ; 
 scalar_t__ stub2 (struct perf_evsel*,struct perf_sample*,struct event_key*) ; 

__attribute__((used)) static bool handle_kvm_event(struct perf_kvm_stat *kvm,
			     struct thread *thread,
			     struct perf_evsel *evsel,
			     struct perf_sample *sample)
{
	struct vcpu_event_record *vcpu_record;
	struct event_key key = {.key = INVALID_KEY};

	vcpu_record = per_vcpu_record(thread, evsel, sample);
	if (!vcpu_record)
		return true;

	/* only process events for vcpus user cares about */
	if ((kvm->trace_vcpu != -1) &&
	    (kvm->trace_vcpu != vcpu_record->vcpu_id))
		return true;

	if (kvm->events_ops->is_begin_event(evsel, sample, &key))
		return handle_begin_event(kvm, vcpu_record, &key, sample->time);

	if (kvm->events_ops->is_end_event(evsel, sample, &key))
		return handle_end_event(kvm, vcpu_record, &key, sample->time);

	return true;
}