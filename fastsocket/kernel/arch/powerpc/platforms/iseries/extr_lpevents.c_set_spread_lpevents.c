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
 unsigned long NR_CPUS ; 
 int /*<<< orphan*/  printk (char*,unsigned long) ; 
 unsigned long simple_strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long spread_lpevents ; 

__attribute__((used)) static int set_spread_lpevents(char *str)
{
	unsigned long val = simple_strtoul(str, NULL, 0);

	/*
	 * The parameter is the number of processors to share in processing
	 * lp events.
	 */
	if (( val > 0) && (val <= NR_CPUS)) {
		spread_lpevents = val;
		printk("lpevent processing spread over %ld processors\n", val);
	} else {
		printk("invalid spread_lpevents %ld\n", val);
	}

	return 1;
}