#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union u64_swap {int val64; void** val32; } ;
struct TYPE_6__ {int size; } ;
struct TYPE_5__ {int* array; } ;
union perf_event {TYPE_3__ header; TYPE_2__ sample; } ;
typedef  int u64 ;
struct perf_sample {int stream_id; int id; int time; void* tid; void* pid; void* cpu; } ;
struct TYPE_4__ {int sample_type; } ;
struct perf_evsel {int needs_swap; TYPE_1__ attr; } ;

/* Variables and functions */
 int PERF_SAMPLE_CPU ; 
 int PERF_SAMPLE_ID ; 
 int PERF_SAMPLE_STREAM_ID ; 
 int PERF_SAMPLE_TID ; 
 int PERF_SAMPLE_TIME ; 
 void* bswap_32 (void*) ; 
 void* bswap_64 (int) ; 

__attribute__((used)) static int perf_evsel__parse_id_sample(const struct perf_evsel *evsel,
				       const union perf_event *event,
				       struct perf_sample *sample)
{
	u64 type = evsel->attr.sample_type;
	const u64 *array = event->sample.array;
	bool swapped = evsel->needs_swap;
	union u64_swap u;

	array += ((event->header.size -
		   sizeof(event->header)) / sizeof(u64)) - 1;

	if (type & PERF_SAMPLE_CPU) {
		u.val64 = *array;
		if (swapped) {
			/* undo swap of u64, then swap on individual u32s */
			u.val64 = bswap_64(u.val64);
			u.val32[0] = bswap_32(u.val32[0]);
		}

		sample->cpu = u.val32[0];
		array--;
	}

	if (type & PERF_SAMPLE_STREAM_ID) {
		sample->stream_id = *array;
		array--;
	}

	if (type & PERF_SAMPLE_ID) {
		sample->id = *array;
		array--;
	}

	if (type & PERF_SAMPLE_TIME) {
		sample->time = *array;
		array--;
	}

	if (type & PERF_SAMPLE_TID) {
		u.val64 = *array;
		if (swapped) {
			/* undo swap of u64, then swap on individual u32s */
			u.val64 = bswap_64(u.val64);
			u.val32[0] = bswap_32(u.val32[0]);
			u.val32[1] = bswap_32(u.val32[1]);
		}

		sample->pid = u.val32[0];
		sample->tid = u.val32[1];
	}

	return 0;
}