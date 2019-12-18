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
typedef  int u64 ;
struct perf_event_attr {int sample_type; } ;
struct perf_evsel {struct perf_event_attr attr; } ;

/* Variables and functions */
 int EINVAL ; 
 char* perf_evsel__name (struct perf_evsel*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,char const*) ; 

__attribute__((used)) static int perf_evsel__check_stype(struct perf_evsel *evsel,
				   u64 sample_type, const char *sample_msg)
{
	struct perf_event_attr *attr = &evsel->attr;
	const char *name = perf_evsel__name(evsel);

	if (!(attr->sample_type & sample_type)) {
		pr_err("Samples for %s event do not have %s attribute set.",
			name, sample_msg);
		return -EINVAL;
	}

	return 0;
}