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
typedef  void* u64 ;
struct cpudata {scalar_t__ prev_idle_time_us; int sample_ptr; void* prev_mperf; void* prev_aperf; void* prev_sample; TYPE_1__* samples; int /*<<< orphan*/  cpu; } ;
typedef  void* ktime_t ;
struct TYPE_2__ {void* mperf; void* aperf; void* idletime_us; int /*<<< orphan*/  duration_us; void* end_time; void* start_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_APERF ; 
 int /*<<< orphan*/  MSR_IA32_MPERF ; 
 int SAMPLE_COUNT ; 
 void* get_cpu_idle_time_us (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_pstate_calc_busy (struct cpudata*,TYPE_1__*) ; 
 void* ktime_get () ; 
 int /*<<< orphan*/  ktime_us_delta (void*,void*) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static inline void intel_pstate_sample(struct cpudata *cpu)
{
	ktime_t now;
	u64 idle_time_us;
	u64 aperf, mperf;

	now = ktime_get();
	idle_time_us = get_cpu_idle_time_us(cpu->cpu, NULL);

	rdmsrl(MSR_IA32_APERF, aperf);
	rdmsrl(MSR_IA32_MPERF, mperf);
	/* for the first sample, don't actually record a sample, just
	 * set the baseline */
	if (cpu->prev_idle_time_us > 0) {
		cpu->sample_ptr = (cpu->sample_ptr + 1) % SAMPLE_COUNT;
		cpu->samples[cpu->sample_ptr].start_time = cpu->prev_sample;
		cpu->samples[cpu->sample_ptr].end_time = now;
		cpu->samples[cpu->sample_ptr].duration_us =
			ktime_us_delta(now, cpu->prev_sample);
		cpu->samples[cpu->sample_ptr].idletime_us =
			idle_time_us - cpu->prev_idle_time_us;

		cpu->samples[cpu->sample_ptr].aperf = aperf;
		cpu->samples[cpu->sample_ptr].mperf = mperf;
		cpu->samples[cpu->sample_ptr].aperf -= cpu->prev_aperf;
		cpu->samples[cpu->sample_ptr].mperf -= cpu->prev_mperf;

		intel_pstate_calc_busy(cpu, &cpu->samples[cpu->sample_ptr]);
	}

	cpu->prev_sample = now;
	cpu->prev_idle_time_us = idle_time_us;
	cpu->prev_aperf = aperf;
	cpu->prev_mperf = mperf;
}