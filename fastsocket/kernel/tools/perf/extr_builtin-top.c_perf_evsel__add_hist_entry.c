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
struct perf_sample {int /*<<< orphan*/  period; } ;
struct perf_evsel {int /*<<< orphan*/  hists; } ;
struct hist_entry {int dummy; } ;
struct addr_location {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_RECORD_SAMPLE ; 
 struct hist_entry* __hists__add_entry (int /*<<< orphan*/ *,struct addr_location*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hists__inc_nr_events (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct hist_entry *perf_evsel__add_hist_entry(struct perf_evsel *evsel,
						     struct addr_location *al,
						     struct perf_sample *sample)
{
	struct hist_entry *he;

	he = __hists__add_entry(&evsel->hists, al, NULL, sample->period);
	if (he == NULL)
		return NULL;

	hists__inc_nr_events(&evsel->hists, PERF_RECORD_SAMPLE);
	return he;
}