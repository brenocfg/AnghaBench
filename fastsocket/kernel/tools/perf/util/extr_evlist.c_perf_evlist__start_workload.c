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
struct TYPE_2__ {scalar_t__ cork_fd; } ;
struct perf_evlist {TYPE_1__ workload; } ;

/* Variables and functions */
 int close (scalar_t__) ; 

int perf_evlist__start_workload(struct perf_evlist *evlist)
{
	if (evlist->workload.cork_fd > 0) {
		/*
		 * Remove the cork, let it rip!
		 */
		return close(evlist->workload.cork_fd);
	}

	return 0;
}