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
struct TYPE_2__ {unsigned int i_flags; } ;
struct jfs_inode_info {int mode2; TYPE_1__ vfs_inode; } ;

/* Variables and functions */
 int JFS_APPEND_FL ; 
 int JFS_DIRSYNC_FL ; 
 int JFS_IMMUTABLE_FL ; 
 int JFS_NOATIME_FL ; 
 int JFS_SYNC_FL ; 
 unsigned int S_APPEND ; 
 unsigned int S_DIRSYNC ; 
 unsigned int S_IMMUTABLE ; 
 unsigned int S_NOATIME ; 
 unsigned int S_SYNC ; 

void jfs_get_inode_flags(struct jfs_inode_info *jfs_ip)
{
	unsigned int flags = jfs_ip->vfs_inode.i_flags;

	jfs_ip->mode2 &= ~(JFS_IMMUTABLE_FL | JFS_APPEND_FL | JFS_NOATIME_FL |
			   JFS_DIRSYNC_FL | JFS_SYNC_FL);
	if (flags & S_IMMUTABLE)
		jfs_ip->mode2 |= JFS_IMMUTABLE_FL;
	if (flags & S_APPEND)
		jfs_ip->mode2 |= JFS_APPEND_FL;
	if (flags & S_NOATIME)
		jfs_ip->mode2 |= JFS_NOATIME_FL;
	if (flags & S_DIRSYNC)
		jfs_ip->mode2 |= JFS_DIRSYNC_FL;
	if (flags & S_SYNC)
		jfs_ip->mode2 |= JFS_SYNC_FL;
}