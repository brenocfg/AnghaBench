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
typedef  scalar_t__ u32 ;
struct ocfs2_orphan_scan {scalar_t__ os_seqno; int /*<<< orphan*/  os_scantime; int /*<<< orphan*/  os_count; int /*<<< orphan*/  os_state; } ;
struct ocfs2_super {int max_slots; int /*<<< orphan*/  journal; struct ocfs2_orphan_scan osb_orphan_scan; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
 int EAGAIN ; 
 scalar_t__ ORPHAN_SCAN_INACTIVE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_orphan_scan_lock (struct ocfs2_super*,scalar_t__*) ; 
 int /*<<< orphan*/  ocfs2_orphan_scan_unlock (struct ocfs2_super*,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_queue_recovery_completion (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ocfs2_queue_orphan_scan(struct ocfs2_super *osb)
{
	struct ocfs2_orphan_scan *os;
	int status, i;
	u32 seqno = 0;

	os = &osb->osb_orphan_scan;

	if (atomic_read(&os->os_state) == ORPHAN_SCAN_INACTIVE)
		goto out;

	status = ocfs2_orphan_scan_lock(osb, &seqno);
	if (status < 0) {
		if (status != -EAGAIN)
			mlog_errno(status);
		goto out;
	}

	/* Do no queue the tasks if the volume is being umounted */
	if (atomic_read(&os->os_state) == ORPHAN_SCAN_INACTIVE)
		goto unlock;

	if (os->os_seqno != seqno) {
		os->os_seqno = seqno;
		goto unlock;
	}

	for (i = 0; i < osb->max_slots; i++)
		ocfs2_queue_recovery_completion(osb->journal, i, NULL, NULL,
						NULL);
	/*
	 * We queued a recovery on orphan slots, increment the sequence
	 * number and update LVB so other node will skip the scan for a while
	 */
	seqno++;
	os->os_count++;
	os->os_scantime = CURRENT_TIME;
unlock:
	ocfs2_orphan_scan_unlock(osb, seqno);
out:
	return;
}