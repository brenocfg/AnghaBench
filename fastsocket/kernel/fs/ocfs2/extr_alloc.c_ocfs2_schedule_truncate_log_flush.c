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
struct ocfs2_super {int /*<<< orphan*/  osb_truncate_log_wq; scalar_t__ osb_tl_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_TRUNCATE_LOG_FLUSH_INTERVAL ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_wq ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ocfs2_schedule_truncate_log_flush(struct ocfs2_super *osb,
				       int cancel)
{
	if (osb->osb_tl_inode) {
		/* We want to push off log flushes while truncates are
		 * still running. */
		if (cancel)
			cancel_delayed_work(&osb->osb_truncate_log_wq);

		queue_delayed_work(ocfs2_wq, &osb->osb_truncate_log_wq,
				   OCFS2_TRUNCATE_LOG_FLUSH_INTERVAL);
	}
}