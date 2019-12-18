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
struct TYPE_2__ {int /*<<< orphan*/  config; } ;
struct perf_evsel {TYPE_1__ attr; } ;

/* Variables and functions */
 int __perf_evsel__hw_cache_name (int /*<<< orphan*/ ,char*,size_t) ; 
 int perf_evsel__add_modifiers (struct perf_evsel*,char*,size_t) ; 

__attribute__((used)) static int perf_evsel__hw_cache_name(struct perf_evsel *evsel, char *bf, size_t size)
{
	int ret = __perf_evsel__hw_cache_name(evsel->attr.config, bf, size);
	return ret + perf_evsel__add_modifiers(evsel, bf + ret, size - ret);
}