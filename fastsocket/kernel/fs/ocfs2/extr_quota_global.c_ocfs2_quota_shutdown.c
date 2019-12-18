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
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ocfs2_quota_wq ; 

void ocfs2_quota_shutdown(void)
{
	if (ocfs2_quota_wq) {
		flush_workqueue(ocfs2_quota_wq);
		destroy_workqueue(ocfs2_quota_wq);
		ocfs2_quota_wq = NULL;
	}
}