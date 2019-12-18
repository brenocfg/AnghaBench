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
typedef  scalar_t__ u32 ;
struct pt_regs {int dummy; } ;
struct perf_sample_data {int dummy; } ;
struct TYPE_2__ {int type; scalar_t__ config; } ;
struct perf_event {TYPE_1__ attr; } ;
typedef  enum perf_type_id { ____Placeholder_perf_type_id } perf_type_id ;

/* Variables and functions */
 scalar_t__ PERF_TYPE_TRACEPOINT ; 
 scalar_t__ perf_exclude_event (struct perf_event*,struct pt_regs*) ; 
 int /*<<< orphan*/  perf_tp_event_match (struct perf_event*,struct perf_sample_data*) ; 

__attribute__((used)) static int perf_swevent_match(struct perf_event *event,
				enum perf_type_id type,
				u32 event_id,
				struct perf_sample_data *data,
				struct pt_regs *regs)
{
	if (event->attr.type != type)
		return 0;

	if (event->attr.config != event_id)
		return 0;

	if (perf_exclude_event(event, regs))
		return 0;

	if (event->attr.type == PERF_TYPE_TRACEPOINT &&
			!perf_tp_event_match(event, data))
		return 0;

	return 1;
}