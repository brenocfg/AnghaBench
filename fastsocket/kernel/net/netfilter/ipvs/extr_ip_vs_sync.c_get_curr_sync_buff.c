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
struct ip_vs_sync_buff {scalar_t__ firstuse; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 struct ip_vs_sync_buff* curr_sb ; 
 int /*<<< orphan*/  curr_sb_lock ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (scalar_t__,unsigned long) ; 

__attribute__((used)) static inline struct ip_vs_sync_buff *
get_curr_sync_buff(unsigned long time)
{
	struct ip_vs_sync_buff *sb;

	spin_lock_bh(&curr_sb_lock);
	if (curr_sb && (time == 0 ||
			time_before(jiffies - curr_sb->firstuse, time))) {
		sb = curr_sb;
		curr_sb = NULL;
		__set_current_state(TASK_RUNNING);
	} else
		sb = NULL;
	spin_unlock_bh(&curr_sb_lock);
	return sb;
}