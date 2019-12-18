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
struct ocfs2_orphan_scan {int /*<<< orphan*/  os_lock; int /*<<< orphan*/  os_orphan_scan_work; int /*<<< orphan*/  os_state; } ;
struct ocfs2_super {struct ocfs2_orphan_scan osb_orphan_scan; } ;

/* Variables and functions */
 scalar_t__ ORPHAN_SCAN_ACTIVE ; 
 int /*<<< orphan*/  ORPHAN_SCAN_INACTIVE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void ocfs2_orphan_scan_stop(struct ocfs2_super *osb)
{
	struct ocfs2_orphan_scan *os;

	os = &osb->osb_orphan_scan;
	if (atomic_read(&os->os_state) == ORPHAN_SCAN_ACTIVE) {
		atomic_set(&os->os_state, ORPHAN_SCAN_INACTIVE);
		mutex_lock(&os->os_lock);
		cancel_delayed_work(&os->os_orphan_scan_work);
		mutex_unlock(&os->os_lock);
	}
}