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
struct ocfs2_super {int /*<<< orphan*/ * quota_rec; int /*<<< orphan*/  slot_num; int /*<<< orphan*/  journal; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocfs2_queue_recovery_completion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ocfs2_complete_quota_recovery(struct ocfs2_super *osb)
{
	if (osb->quota_rec) {
		ocfs2_queue_recovery_completion(osb->journal,
						osb->slot_num,
						NULL,
						NULL,
						osb->quota_rec);
		osb->quota_rec = NULL;
	}
}