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
struct perf_evsel {int dummy; } ;
struct perf_evlist {struct perf_evsel* selected; } ;

/* Variables and functions */

void perf_evlist__set_selected(struct perf_evlist *evlist,
			       struct perf_evsel *evsel)
{
	evlist->selected = evsel;
}