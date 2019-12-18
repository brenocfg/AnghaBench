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
struct perf_evsel {int /*<<< orphan*/  ids; int /*<<< orphan*/ * id; } ;
struct perf_evlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_evlist__id_hash (struct perf_evlist*,struct perf_evsel*,int,int,int /*<<< orphan*/ ) ; 

void perf_evlist__id_add(struct perf_evlist *evlist, struct perf_evsel *evsel,
			 int cpu, int thread, u64 id)
{
	perf_evlist__id_hash(evlist, evsel, cpu, thread, id);
	evsel->id[evsel->ids++] = id;
}