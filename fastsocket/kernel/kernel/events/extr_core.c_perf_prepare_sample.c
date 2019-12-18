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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct pt_regs {int dummy; } ;
struct perf_sample_data {TYPE_3__* br_stack; TYPE_2__* raw; TYPE_4__* callchain; int /*<<< orphan*/  ip; } ;
struct perf_event_header {scalar_t__ size; int /*<<< orphan*/  misc; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int sample_type; } ;
struct perf_event {scalar_t__ header_size; TYPE_1__ attr; } ;
struct perf_branch_entry {int dummy; } ;
struct TYPE_8__ {scalar_t__ nr; } ;
struct TYPE_7__ {int nr; } ;
struct TYPE_6__ {scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_RECORD_SAMPLE ; 
 int PERF_SAMPLE_BRANCH_STACK ; 
 int PERF_SAMPLE_CALLCHAIN ; 
 int PERF_SAMPLE_IP ; 
 int PERF_SAMPLE_RAW ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __perf_event_header__init_id (struct perf_event_header*,struct perf_sample_data*,struct perf_event*) ; 
 TYPE_4__* perf_callchain (struct pt_regs*) ; 
 int /*<<< orphan*/  perf_instruction_pointer (struct pt_regs*) ; 
 int /*<<< orphan*/  perf_misc_flags (struct pt_regs*) ; 

void perf_prepare_sample(struct perf_event_header *header,
			 struct perf_sample_data *data,
			 struct perf_event *event,
			 struct pt_regs *regs)
{
	u64 sample_type = event->attr.sample_type;

	header->type = PERF_RECORD_SAMPLE;
	header->size = sizeof(*header) + event->header_size;

	header->misc = 0;
	header->misc |= perf_misc_flags(regs);

	__perf_event_header__init_id(header, data, event);

	if (sample_type & PERF_SAMPLE_IP)
		data->ip = perf_instruction_pointer(regs);

	if (sample_type & PERF_SAMPLE_CALLCHAIN) {
		int size = 1;

		data->callchain = perf_callchain(regs);

		if (data->callchain)
			size += data->callchain->nr;

		header->size += size * sizeof(u64);
	}

	if (sample_type & PERF_SAMPLE_RAW) {
		int size = sizeof(u32);

		if (data->raw)
			size += data->raw->size;
		else
			size += sizeof(u32);

		WARN_ON_ONCE(size & (sizeof(u64)-1));
		header->size += size;
	}

	if (sample_type & PERF_SAMPLE_BRANCH_STACK) {
		int size = sizeof(u64); /* nr */
		if (data->br_stack) {
			size += data->br_stack->nr
			      * sizeof(struct perf_branch_entry);
		}
		header->size += size;
	}
}