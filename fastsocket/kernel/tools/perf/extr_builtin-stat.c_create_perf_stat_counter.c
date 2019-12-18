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
struct perf_event_attr {int read_format; int inherit; int disabled; int enable_on_exec; scalar_t__ exclude_host; scalar_t__ exclude_guest; } ;
struct perf_evsel {struct perf_event_attr attr; } ;
struct TYPE_2__ {int /*<<< orphan*/  threads; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int PERF_FORMAT_TOTAL_TIME_ENABLED ; 
 int PERF_FORMAT_TOTAL_TIME_RUNNING ; 
 scalar_t__ errno ; 
 TYPE_1__* evsel_list ; 
 int /*<<< orphan*/  no_inherit ; 
 int /*<<< orphan*/  perf_evsel__cpus (struct perf_evsel*) ; 
 int /*<<< orphan*/  perf_evsel__is_group_member (struct perf_evsel*) ; 
 int perf_evsel__open_per_cpu (struct perf_evsel*,int /*<<< orphan*/ ) ; 
 int perf_evsel__open_per_thread (struct perf_evsel*,int /*<<< orphan*/ ) ; 
 scalar_t__ perf_target__has_cpu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_target__has_task (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 scalar_t__ scale ; 
 int /*<<< orphan*/  target ; 

__attribute__((used)) static int create_perf_stat_counter(struct perf_evsel *evsel)
{
	struct perf_event_attr *attr = &evsel->attr;
	bool exclude_guest_missing = false;
	int ret;

	if (scale)
		attr->read_format = PERF_FORMAT_TOTAL_TIME_ENABLED |
				    PERF_FORMAT_TOTAL_TIME_RUNNING;

	attr->inherit = !no_inherit;

retry:
	if (exclude_guest_missing)
		evsel->attr.exclude_guest = evsel->attr.exclude_host = 0;

	if (perf_target__has_cpu(&target)) {
		ret = perf_evsel__open_per_cpu(evsel, perf_evsel__cpus(evsel));
		if (ret)
			goto check_ret;
		return 0;
	}

	if (!perf_target__has_task(&target) &&
	    !perf_evsel__is_group_member(evsel)) {
		attr->disabled = 1;
		attr->enable_on_exec = 1;
	}

	ret = perf_evsel__open_per_thread(evsel, evsel_list->threads);
	if (!ret)
		return 0;
	/* fall through */
check_ret:
	if (ret && errno == EINVAL) {
		if (!exclude_guest_missing &&
		    (evsel->attr.exclude_guest || evsel->attr.exclude_host)) {
			pr_debug("Old kernel, cannot exclude "
				 "guest or host samples.\n");
			exclude_guest_missing = true;
			goto retry;
		}
	}
	return ret;
}