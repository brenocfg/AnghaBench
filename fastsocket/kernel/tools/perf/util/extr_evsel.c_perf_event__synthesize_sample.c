#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union u64_swap {int val64; void** val32; } ;
struct TYPE_4__ {int /*<<< orphan*/  ip; } ;
struct TYPE_3__ {int* array; } ;
union perf_event {TYPE_2__ ip; TYPE_1__ sample; } ;
typedef  int u64 ;
struct perf_sample {int time; int addr; int id; int stream_id; int period; void* cpu; void* tid; void* pid; int /*<<< orphan*/  ip; } ;

/* Variables and functions */
 int PERF_SAMPLE_ADDR ; 
 int PERF_SAMPLE_CPU ; 
 int PERF_SAMPLE_ID ; 
 int PERF_SAMPLE_IP ; 
 int PERF_SAMPLE_PERIOD ; 
 int PERF_SAMPLE_STREAM_ID ; 
 int PERF_SAMPLE_TID ; 
 int PERF_SAMPLE_TIME ; 
 void* bswap_32 (void*) ; 
 void* bswap_64 (int) ; 

int perf_event__synthesize_sample(union perf_event *event, u64 type,
				  const struct perf_sample *sample,
				  bool swapped)
{
	u64 *array;

	/*
	 * used for cross-endian analysis. See git commit 65014ab3
	 * for why this goofiness is needed.
	 */
	union u64_swap u;

	array = event->sample.array;

	if (type & PERF_SAMPLE_IP) {
		event->ip.ip = sample->ip;
		array++;
	}

	if (type & PERF_SAMPLE_TID) {
		u.val32[0] = sample->pid;
		u.val32[1] = sample->tid;
		if (swapped) {
			/*
			 * Inverse of what is done in perf_evsel__parse_sample
			 */
			u.val32[0] = bswap_32(u.val32[0]);
			u.val32[1] = bswap_32(u.val32[1]);
			u.val64 = bswap_64(u.val64);
		}

		*array = u.val64;
		array++;
	}

	if (type & PERF_SAMPLE_TIME) {
		*array = sample->time;
		array++;
	}

	if (type & PERF_SAMPLE_ADDR) {
		*array = sample->addr;
		array++;
	}

	if (type & PERF_SAMPLE_ID) {
		*array = sample->id;
		array++;
	}

	if (type & PERF_SAMPLE_STREAM_ID) {
		*array = sample->stream_id;
		array++;
	}

	if (type & PERF_SAMPLE_CPU) {
		u.val32[0] = sample->cpu;
		if (swapped) {
			/*
			 * Inverse of what is done in perf_evsel__parse_sample
			 */
			u.val32[0] = bswap_32(u.val32[0]);
			u.val64 = bswap_64(u.val64);
		}
		*array = u.val64;
		array++;
	}

	if (type & PERF_SAMPLE_PERIOD) {
		*array = sample->period;
		array++;
	}

	return 0;
}