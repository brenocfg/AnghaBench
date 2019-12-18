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
struct s3c2410_dma_stats {int timeout_longest; int timeout_shortest; int timeout_avg; } ;

/* Variables and functions */

__attribute__((used)) static void
s3c2410_dma_stats_timeout(struct s3c2410_dma_stats *stats, int val)
{
	if (stats == NULL)
		return;

	if (val > stats->timeout_longest)
		stats->timeout_longest = val;
	if (val < stats->timeout_shortest)
		stats->timeout_shortest = val;

	stats->timeout_avg += val;
}