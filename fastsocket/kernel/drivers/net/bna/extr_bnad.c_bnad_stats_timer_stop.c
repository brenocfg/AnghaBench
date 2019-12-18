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
struct bnad {int /*<<< orphan*/  stats_timer; int /*<<< orphan*/  bna_lock; int /*<<< orphan*/  run_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNAD_RF_STATS_TIMER_RUNNING ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bnad_stats_timer_stop(struct bnad *bnad)
{
	int to_del = 0;
	unsigned long flags;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	if (test_and_clear_bit(BNAD_RF_STATS_TIMER_RUNNING, &bnad->run_flags))
		to_del = 1;
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
	if (to_del)
		del_timer_sync(&bnad->stats_timer);
}