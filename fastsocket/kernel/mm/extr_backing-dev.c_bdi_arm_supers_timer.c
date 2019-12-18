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
 int dirty_writeback_interval ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  round_jiffies_up (unsigned long) ; 
 int /*<<< orphan*/  sync_supers_timer ; 

void bdi_arm_supers_timer(void)
{
	unsigned long next;

	if (!dirty_writeback_interval)
		return;

	next = msecs_to_jiffies(dirty_writeback_interval * 10) + jiffies;
	mod_timer(&sync_supers_timer, round_jiffies_up(next));
}