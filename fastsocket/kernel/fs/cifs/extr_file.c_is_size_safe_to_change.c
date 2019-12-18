#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cifs_sb_info {int mnt_cifs_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_sb; } ;
struct cifsInodeInfo {TYPE_1__ vfs_inode; } ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 int CIFS_MOUNT_DIRECT_IO ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ i_size_read (TYPE_1__*) ; 
 scalar_t__ is_inode_writable (struct cifsInodeInfo*) ; 

bool is_size_safe_to_change(struct cifsInodeInfo *cifsInode, __u64 end_of_file)
{
	if (!cifsInode)
		return true;

	if (is_inode_writable(cifsInode)) {
		/* This inode is open for write at least once */
		struct cifs_sb_info *cifs_sb;

		cifs_sb = CIFS_SB(cifsInode->vfs_inode.i_sb);
		if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_DIRECT_IO) {
			/* since no page cache to corrupt on directio
			we can change size safely */
			return true;
		}

		if (i_size_read(&cifsInode->vfs_inode) < end_of_file)
			return true;

		return false;
	} else
		return true;
}