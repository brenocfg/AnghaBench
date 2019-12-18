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
struct msm_sync {int unblock_poll_frame; int /*<<< orphan*/  prev_frame_q_lock; int /*<<< orphan*/  prev_frame_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDBG (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int msm_unblock_poll_frame(struct msm_sync *sync)
{
	unsigned long flags;
	CDBG("msm_unblock_poll_frame\n");
	spin_lock_irqsave(&sync->prev_frame_q_lock, flags);
	sync->unblock_poll_frame = 1;
	wake_up(&sync->prev_frame_wait);
	spin_unlock_irqrestore(&sync->prev_frame_q_lock, flags);
	return 0;
}