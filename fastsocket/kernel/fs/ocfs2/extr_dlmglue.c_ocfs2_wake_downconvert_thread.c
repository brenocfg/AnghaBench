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
struct ocfs2_super {int /*<<< orphan*/  dc_event; int /*<<< orphan*/  dc_task_lock; int /*<<< orphan*/  dc_wake_sequence; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void ocfs2_wake_downconvert_thread(struct ocfs2_super *osb)
{
	spin_lock(&osb->dc_task_lock);
	/* make sure the voting thread gets a swipe at whatever changes
	 * the caller may have made to the voting state */
	osb->dc_wake_sequence++;
	spin_unlock(&osb->dc_task_lock);
	wake_up(&osb->dc_event);
}