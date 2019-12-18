#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tblock {int /*<<< orphan*/  sb; int /*<<< orphan*/  cqueue; } ;
struct TYPE_4__ {int commit_state; } ;
struct TYPE_3__ {int /*<<< orphan*/  unlock_queue; } ;

/* Variables and functions */
 int IN_LAZYCOMMIT ; 
 TYPE_2__* JFS_SBI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LAZY_LOCK (unsigned long) ; 
 int /*<<< orphan*/  LAZY_UNLOCK (unsigned long) ; 
 TYPE_1__ TxAnchor ; 
 int /*<<< orphan*/  jfs_commit_thread_wait ; 
 int jfs_commit_thread_waking ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void txLazyUnlock(struct tblock * tblk)
{
	unsigned long flags;

	LAZY_LOCK(flags);

	list_add_tail(&tblk->cqueue, &TxAnchor.unlock_queue);
	/*
	 * Don't wake up a commit thread if there is already one servicing
	 * this superblock, or if the last one we woke up hasn't started yet.
	 */
	if (!(JFS_SBI(tblk->sb)->commit_state & IN_LAZYCOMMIT) &&
	    !jfs_commit_thread_waking) {
		jfs_commit_thread_waking = 1;
		wake_up(&jfs_commit_thread_wait);
	}
	LAZY_UNLOCK(flags);
}