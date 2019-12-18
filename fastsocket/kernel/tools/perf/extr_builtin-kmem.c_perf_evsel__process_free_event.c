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
struct perf_sample {scalar_t__ cpu; } ;
struct perf_evsel {int dummy; } ;
struct alloc_stat {short alloc_cpu; int /*<<< orphan*/  pingpong; int /*<<< orphan*/  call_site; } ;

/* Variables and functions */
 int /*<<< orphan*/  callsite_cmp ; 
 unsigned long perf_evsel__intval (struct perf_evsel*,struct perf_sample*,char*) ; 
 int /*<<< orphan*/  ptr_cmp ; 
 int /*<<< orphan*/  root_alloc_stat ; 
 int /*<<< orphan*/  root_caller_stat ; 
 struct alloc_stat* search_alloc_stat (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int perf_evsel__process_free_event(struct perf_evsel *evsel,
					  struct perf_sample *sample)
{
	unsigned long ptr = perf_evsel__intval(evsel, sample, "ptr");
	struct alloc_stat *s_alloc, *s_caller;

	s_alloc = search_alloc_stat(ptr, 0, &root_alloc_stat, ptr_cmp);
	if (!s_alloc)
		return 0;

	if ((short)sample->cpu != s_alloc->alloc_cpu) {
		s_alloc->pingpong++;

		s_caller = search_alloc_stat(0, s_alloc->call_site,
					     &root_caller_stat, callsite_cmp);
		if (!s_caller)
			return -1;
		s_caller->pingpong++;
	}
	s_alloc->alloc_cpu = -1;

	return 0;
}