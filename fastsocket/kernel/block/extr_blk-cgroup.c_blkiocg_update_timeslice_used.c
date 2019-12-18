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
struct TYPE_2__ {unsigned long time; } ;
struct blkio_group {int /*<<< orphan*/  stats_lock; TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void blkiocg_update_timeslice_used(struct blkio_group *blkg, unsigned long time)
{
	unsigned long flags;

	spin_lock_irqsave(&blkg->stats_lock, flags);
	blkg->stats.time += time;
	spin_unlock_irqrestore(&blkg->stats_lock, flags);
}