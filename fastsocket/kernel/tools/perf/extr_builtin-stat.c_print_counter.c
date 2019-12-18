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
typedef  double u64 ;
struct perf_evsel {TYPE_3__* cgrp; scalar_t__ supported; TYPE_2__* counts; } ;
struct TYPE_8__ {char** map; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_1__* cpu; } ;
struct TYPE_5__ {double val; double ena; double run; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNTR_NOT_COUNTED ; 
 int /*<<< orphan*/  CNTR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  abs_printout (int,struct perf_evsel*,double) ; 
 scalar_t__ csv_output ; 
 char* csv_sep ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 scalar_t__ nsec_counter (struct perf_evsel*) ; 
 int /*<<< orphan*/  nsec_printout (int,struct perf_evsel*,double) ; 
 int /*<<< orphan*/  output ; 
 TYPE_4__* perf_evsel__cpus (struct perf_evsel*) ; 
 int /*<<< orphan*/  perf_evsel__name (struct perf_evsel*) ; 
 int perf_evsel__nr_cpus (struct perf_evsel*) ; 
 int /*<<< orphan*/  print_noise (struct perf_evsel*,double) ; 

__attribute__((used)) static void print_counter(struct perf_evsel *counter)
{
	u64 ena, run, val;
	int cpu;

	for (cpu = 0; cpu < perf_evsel__nr_cpus(counter); cpu++) {
		val = counter->counts->cpu[cpu].val;
		ena = counter->counts->cpu[cpu].ena;
		run = counter->counts->cpu[cpu].run;
		if (run == 0 || ena == 0) {
			fprintf(output, "CPU%*d%s%*s%s%*s",
				csv_output ? 0 : -4,
				perf_evsel__cpus(counter)->map[cpu], csv_sep,
				csv_output ? 0 : 18,
				counter->supported ? CNTR_NOT_COUNTED : CNTR_NOT_SUPPORTED,
				csv_sep,
				csv_output ? 0 : -24,
				perf_evsel__name(counter));

			if (counter->cgrp)
				fprintf(output, "%s%s",
					csv_sep, counter->cgrp->name);

			fputc('\n', output);
			continue;
		}

		if (nsec_counter(counter))
			nsec_printout(cpu, counter, val);
		else
			abs_printout(cpu, counter, val);

		if (!csv_output) {
			print_noise(counter, 1.0);

			if (run != ena)
				fprintf(output, "  (%.2f%%)",
					100.0 * run / ena);
		}
		fputc('\n', output);
	}
}