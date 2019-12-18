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
struct ext4_inode_info {unsigned long i_flags; TYPE_1__ vfs_inode; } ;

/* Variables and functions */
 unsigned long EXT4_APPEND_FL ; 
 unsigned long EXT4_DIRSYNC_FL ; 
 unsigned long EXT4_IMMUTABLE_FL ; 
 unsigned long EXT4_NOATIME_FL ; 
 unsigned long EXT4_SYNC_FL ; 
 unsigned int S_APPEND ; 
 unsigned int S_DIRSYNC ; 
 unsigned int S_IMMUTABLE ; 
 unsigned int S_NOATIME ; 
 unsigned int S_SYNC ; 
 unsigned long cmpxchg (unsigned long*,unsigned long,unsigned long) ; 

void ext4_get_inode_flags(struct ext4_inode_info *ei)
{
	unsigned int vfs_fl;
	unsigned long old_fl, new_fl;

	do {
		vfs_fl = ei->vfs_inode.i_flags;
		old_fl = ei->i_flags;
		new_fl = old_fl & ~(EXT4_SYNC_FL|EXT4_APPEND_FL|
				EXT4_IMMUTABLE_FL|EXT4_NOATIME_FL|
				EXT4_DIRSYNC_FL);
		if (vfs_fl & S_SYNC)
			new_fl |= EXT4_SYNC_FL;
		if (vfs_fl & S_APPEND)
			new_fl |= EXT4_APPEND_FL;
		if (vfs_fl & S_IMMUTABLE)
			new_fl |= EXT4_IMMUTABLE_FL;
		if (vfs_fl & S_NOATIME)
			new_fl |= EXT4_NOATIME_FL;
		if (vfs_fl & S_DIRSYNC)
			new_fl |= EXT4_DIRSYNC_FL;
	} while (cmpxchg(&ei->i_flags, old_fl, new_fl) != old_fl);
}