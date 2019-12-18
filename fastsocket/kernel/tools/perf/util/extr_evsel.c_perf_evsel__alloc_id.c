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
typedef  int /*<<< orphan*/  u64 ;
struct perf_sample_id {int dummy; } ;
struct perf_evsel {int /*<<< orphan*/ * sample_id; int /*<<< orphan*/ * id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  xyarray__delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xyarray__new (int,int,int) ; 
 int /*<<< orphan*/ * zalloc (int) ; 

int perf_evsel__alloc_id(struct perf_evsel *evsel, int ncpus, int nthreads)
{
	evsel->sample_id = xyarray__new(ncpus, nthreads, sizeof(struct perf_sample_id));
	if (evsel->sample_id == NULL)
		return -ENOMEM;

	evsel->id = zalloc(ncpus * nthreads * sizeof(u64));
	if (evsel->id == NULL) {
		xyarray__delete(evsel->sample_id);
		evsel->sample_id = NULL;
		return -ENOMEM;
	}

	return 0;
}