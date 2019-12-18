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
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getprogname () ; 

__attribute__((used)) static void __attribute__((noreturn))
usage()
{
	errx(EX_USAGE, "Usage: %s <threads> <chain | hop | broadcast-single-sem | broadcast-per-thread> "
	     "<realtime | timeshare | fixed> <iterations>\n\t\t"
	     "[--trace <traceworthy latency in ns>] "
	     "[--verbose] [--spin-one] [--spin-all] [--spin-time <nanos>] [--affinity]\n\t\t"
	     "[--no-sleep] [--drop-priority] [--churn-pri <pri>] [--churn-count <n>]",
	     getprogname());
}