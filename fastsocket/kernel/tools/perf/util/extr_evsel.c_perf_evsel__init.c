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
struct perf_event_attr {int /*<<< orphan*/  sample_type; } ;
struct perf_evsel {int idx; int /*<<< orphan*/  sample_size; int /*<<< orphan*/  hists; int /*<<< orphan*/  node; struct perf_event_attr attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __perf_evsel__sample_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hists__init (int /*<<< orphan*/ *) ; 

void perf_evsel__init(struct perf_evsel *evsel,
		      struct perf_event_attr *attr, int idx)
{
	evsel->idx	   = idx;
	evsel->attr	   = *attr;
	INIT_LIST_HEAD(&evsel->node);
	hists__init(&evsel->hists);
	evsel->sample_size = __perf_evsel__sample_size(attr->sample_type);
}