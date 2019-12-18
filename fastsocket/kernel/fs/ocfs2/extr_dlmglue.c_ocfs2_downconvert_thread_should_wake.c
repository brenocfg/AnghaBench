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
struct ocfs2_super {scalar_t__ dc_work_sequence; scalar_t__ dc_wake_sequence; int /*<<< orphan*/  dc_task_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_downconvert_thread_should_wake(struct ocfs2_super *osb)
{
	int should_wake = 0;

	spin_lock(&osb->dc_task_lock);
	if (osb->dc_work_sequence != osb->dc_wake_sequence)
		should_wake = 1;
	spin_unlock(&osb->dc_task_lock);

	return should_wake;
}