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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int read_format; } ;
struct perf_evsel {TYPE_1__ attr; } ;
struct perf_evlist {int dummy; } ;
typedef  int /*<<< orphan*/  read_data ;

/* Variables and functions */
 int PERF_FORMAT_ID ; 
 int PERF_FORMAT_TOTAL_TIME_ENABLED ; 
 int PERF_FORMAT_TOTAL_TIME_RUNNING ; 
 int /*<<< orphan*/  perf_evlist__id_add (struct perf_evlist*,struct perf_evsel*,int,int,int /*<<< orphan*/ ) ; 
 int read (int,int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static int perf_evlist__id_add_fd(struct perf_evlist *evlist,
				  struct perf_evsel *evsel,
				  int cpu, int thread, int fd)
{
	u64 read_data[4] = { 0, };
	int id_idx = 1; /* The first entry is the counter value */

	if (!(evsel->attr.read_format & PERF_FORMAT_ID) ||
	    read(fd, &read_data, sizeof(read_data)) == -1)
		return -1;

	if (evsel->attr.read_format & PERF_FORMAT_TOTAL_TIME_ENABLED)
		++id_idx;
	if (evsel->attr.read_format & PERF_FORMAT_TOTAL_TIME_RUNNING)
		++id_idx;

	perf_evlist__id_add(evlist, evsel, cpu, thread, read_data[id_idx]);
	return 0;
}