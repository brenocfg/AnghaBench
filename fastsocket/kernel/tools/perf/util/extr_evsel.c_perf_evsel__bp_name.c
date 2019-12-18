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
struct perf_event_attr {int /*<<< orphan*/  bp_type; int /*<<< orphan*/  bp_addr; } ;
struct perf_evsel {struct perf_event_attr attr; } ;

/* Variables and functions */
 int __perf_evsel__bp_name (char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int perf_evsel__add_modifiers (struct perf_evsel*,char*,size_t) ; 

__attribute__((used)) static int perf_evsel__bp_name(struct perf_evsel *evsel, char *bf, size_t size)
{
	struct perf_event_attr *attr = &evsel->attr;
	int r = __perf_evsel__bp_name(bf, size, attr->bp_addr, attr->bp_type);
	return r + perf_evsel__add_modifiers(evsel, bf + r, size - r);
}