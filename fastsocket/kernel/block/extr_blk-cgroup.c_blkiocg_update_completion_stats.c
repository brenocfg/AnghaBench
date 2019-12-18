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
typedef  unsigned long long uint64_t ;
struct blkio_group_stats {int /*<<< orphan*/ * stat_arr; } ;
struct blkio_group {int /*<<< orphan*/  stats_lock; struct blkio_group_stats stats; } ;

/* Variables and functions */
 size_t BLKIO_STAT_SERVICE_TIME ; 
 size_t BLKIO_STAT_WAIT_TIME ; 
 int /*<<< orphan*/  blkio_add_stat (int /*<<< orphan*/ ,unsigned long long,int,int) ; 
 unsigned long long sched_clock () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_after64 (unsigned long long,unsigned long long) ; 

void blkiocg_update_completion_stats(struct blkio_group *blkg,
	uint64_t start_time, uint64_t io_start_time, bool direction, bool sync)
{
	struct blkio_group_stats *stats;
	unsigned long flags;
	unsigned long long now = sched_clock();

	spin_lock_irqsave(&blkg->stats_lock, flags);
	stats = &blkg->stats;
	if (time_after64(now, io_start_time))
		blkio_add_stat(stats->stat_arr[BLKIO_STAT_SERVICE_TIME],
				now - io_start_time, direction, sync);
	if (time_after64(io_start_time, start_time))
		blkio_add_stat(stats->stat_arr[BLKIO_STAT_WAIT_TIME],
				io_start_time - start_time, direction, sync);
	spin_unlock_irqrestore(&blkg->stats_lock, flags);
}