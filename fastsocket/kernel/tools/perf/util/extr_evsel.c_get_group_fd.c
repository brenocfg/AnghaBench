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
struct perf_evsel {int /*<<< orphan*/  fd; struct perf_evsel* leader; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int FD (struct perf_evsel*,int,int) ; 
 int /*<<< orphan*/  perf_evsel__is_group_member (struct perf_evsel*) ; 

__attribute__((used)) static int get_group_fd(struct perf_evsel *evsel, int cpu, int thread)
{
	struct perf_evsel *leader = evsel->leader;
	int fd;

	if (!perf_evsel__is_group_member(evsel))
		return -1;

	/*
	 * Leader must be already processed/open,
	 * if not it's a bug.
	 */
	BUG_ON(!leader->fd);

	fd = FD(leader, cpu, thread);
	BUG_ON(fd == -1);

	return fd;
}