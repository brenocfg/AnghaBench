#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct TYPE_7__ {int /*<<< orphan*/ * base_ntfs_ino; int /*<<< orphan*/ * extent_ntfs_inos; } ;
struct TYPE_8__ {int nr_extents; TYPE_1__ ext; } ;
typedef  TYPE_2__ ntfs_inode ;

/* Variables and functions */
 scalar_t__ NInoAttr (TYPE_2__*) ; 
 scalar_t__ NInoDirty (TYPE_2__*) ; 
 TYPE_2__* NTFS_I (struct inode*) ; 
 int /*<<< orphan*/  VFS_I (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __ntfs_clear_inode (TYPE_2__*) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntfs_clear_extent_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntfs_commit_inode (struct inode*) ; 
 int /*<<< orphan*/  ntfs_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void ntfs_clear_big_inode(struct inode *vi)
{
	ntfs_inode *ni = NTFS_I(vi);

#ifdef NTFS_RW
	if (NInoDirty(ni)) {
		bool was_bad = (is_bad_inode(vi));

		/* Committing the inode also commits all extent inodes. */
		ntfs_commit_inode(vi);

		if (!was_bad && (is_bad_inode(vi) || NInoDirty(ni))) {
			ntfs_error(vi->i_sb, "Failed to commit dirty inode "
					"0x%lx.  Losing data!", vi->i_ino);
			// FIXME:  Do something!!!
		}
	}
#endif /* NTFS_RW */

	/* No need to lock at this stage as no one else has a reference. */
	if (ni->nr_extents > 0) {
		int i;

		for (i = 0; i < ni->nr_extents; i++)
			ntfs_clear_extent_inode(ni->ext.extent_ntfs_inos[i]);
		kfree(ni->ext.extent_ntfs_inos);
	}

	__ntfs_clear_inode(ni);

	if (NInoAttr(ni)) {
		/* Release the base inode if we are holding it. */
		if (ni->nr_extents == -1) {
			iput(VFS_I(ni->ext.base_ntfs_ino));
			ni->nr_extents = 0;
			ni->ext.base_ntfs_ino = NULL;
		}
	}
	return;
}