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
struct perf_evsel {TYPE_1__* cgrp; } ;
struct TYPE_4__ {int /*<<< orphan*/ * map; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOFTWARE ; 
 int /*<<< orphan*/  SW_TASK_CLOCK ; 
 double avg_stats (int /*<<< orphan*/ *) ; 
 scalar_t__ csv_output ; 
 char* csv_sep ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char const*,...) ; 
 scalar_t__ no_aggr ; 
 int /*<<< orphan*/  output ; 
 TYPE_2__* perf_evsel__cpus (struct perf_evsel*) ; 
 scalar_t__ perf_evsel__match (struct perf_evsel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_evsel__name (struct perf_evsel*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  walltime_nsecs_stats ; 

__attribute__((used)) static void nsec_printout(int cpu, struct perf_evsel *evsel, double avg)
{
	double msecs = avg / 1e6;
	char cpustr[16] = { '\0', };
	const char *fmt = csv_output ? "%s%.6f%s%s" : "%s%18.6f%s%-25s";

	if (no_aggr)
		sprintf(cpustr, "CPU%*d%s",
			csv_output ? 0 : -4,
			perf_evsel__cpus(evsel)->map[cpu], csv_sep);

	fprintf(output, fmt, cpustr, msecs, csv_sep, perf_evsel__name(evsel));

	if (evsel->cgrp)
		fprintf(output, "%s%s", csv_sep, evsel->cgrp->name);

	if (csv_output)
		return;

	if (perf_evsel__match(evsel, SOFTWARE, SW_TASK_CLOCK))
		fprintf(output, " # %8.3f CPUs utilized          ",
			avg / avg_stats(&walltime_nsecs_stats));
	else
		fprintf(output, "                                   ");
}