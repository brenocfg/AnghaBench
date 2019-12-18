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

/* Variables and functions */
 int /*<<< orphan*/  perf_evsel__hw_names ; 
 int perf_evsel__name_array_test (int /*<<< orphan*/ ) ; 
 int perf_evsel__roundtrip_cache_name_test () ; 
 int /*<<< orphan*/  perf_evsel__sw_names ; 

int test__perf_evsel__roundtrip_name_test(void)
{
	int err = 0, ret = 0;

	err = perf_evsel__name_array_test(perf_evsel__hw_names);
	if (err)
		ret = err;

	err = perf_evsel__name_array_test(perf_evsel__sw_names);
	if (err)
		ret = err;

	err = perf_evsel__roundtrip_cache_name_test();
	if (err)
		ret = err;

	return ret;
}