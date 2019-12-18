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
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ ENOSYS ; 
 int /*<<< orphan*/  clock_attr ; 
 scalar_t__ clock_fd ; 
 int /*<<< orphan*/  die (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  getpid () ; 
 scalar_t__ sys_perf_event_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_clock(void)
{
	clock_fd = sys_perf_event_open(&clock_attr, getpid(), -1, -1, 0);

	if (clock_fd < 0 && errno == ENOSYS)
		die("No CONFIG_PERF_EVENTS=y kernel support configured?\n");
	else
		BUG_ON(clock_fd < 0);
}