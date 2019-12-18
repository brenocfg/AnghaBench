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
struct perf_tool {int /*<<< orphan*/ * finished_round; scalar_t__ ordered_samples; int /*<<< orphan*/ * build_id; int /*<<< orphan*/ * tracing_data; int /*<<< orphan*/ * event_type; int /*<<< orphan*/ * attr; int /*<<< orphan*/ * unthrottle; int /*<<< orphan*/ * throttle; int /*<<< orphan*/ * read; int /*<<< orphan*/ * lost; int /*<<< orphan*/ * exit; int /*<<< orphan*/ * fork; int /*<<< orphan*/ * comm; int /*<<< orphan*/ * mmap; int /*<<< orphan*/ * sample; } ;

/* Variables and functions */
 int /*<<< orphan*/ * perf_event__process_lost ; 
 void* process_event_sample_stub ; 
 void* process_event_stub ; 
 int /*<<< orphan*/ * process_event_synth_attr_stub ; 
 int /*<<< orphan*/ * process_event_synth_tracing_data_stub ; 
 int /*<<< orphan*/ * process_event_type_stub ; 
 int /*<<< orphan*/ * process_finished_round ; 
 void* process_finished_round_stub ; 

__attribute__((used)) static void perf_tool__fill_defaults(struct perf_tool *tool)
{
	if (tool->sample == NULL)
		tool->sample = process_event_sample_stub;
	if (tool->mmap == NULL)
		tool->mmap = process_event_stub;
	if (tool->comm == NULL)
		tool->comm = process_event_stub;
	if (tool->fork == NULL)
		tool->fork = process_event_stub;
	if (tool->exit == NULL)
		tool->exit = process_event_stub;
	if (tool->lost == NULL)
		tool->lost = perf_event__process_lost;
	if (tool->read == NULL)
		tool->read = process_event_sample_stub;
	if (tool->throttle == NULL)
		tool->throttle = process_event_stub;
	if (tool->unthrottle == NULL)
		tool->unthrottle = process_event_stub;
	if (tool->attr == NULL)
		tool->attr = process_event_synth_attr_stub;
	if (tool->event_type == NULL)
		tool->event_type = process_event_type_stub;
	if (tool->tracing_data == NULL)
		tool->tracing_data = process_event_synth_tracing_data_stub;
	if (tool->build_id == NULL)
		tool->build_id = process_finished_round_stub;
	if (tool->finished_round == NULL) {
		if (tool->ordered_samples)
			tool->finished_round = process_finished_round;
		else
			tool->finished_round = process_finished_round_stub;
	}
}