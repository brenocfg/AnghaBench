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
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 

void
print_stats_fract(const char *label, double avg, double max, double min, double stddev)
{
	printf("Max %s jitter: %.1lf%%\n", label, max * 100);
	printf("Min %s jitter: %.1lf%%\n", label, min * 100);
	printf("Avg %s jitter: %.1lf%%\n", label, avg * 100);
	printf("Stddev: %.1lf%%\n", stddev * 100);
	putchar('\n');	
}