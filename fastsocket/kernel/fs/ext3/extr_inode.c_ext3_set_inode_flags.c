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
struct inode {int i_flags; } ;
struct TYPE_2__ {unsigned int i_flags; } ;

/* Variables and functions */
 unsigned int EXT3_APPEND_FL ; 
 unsigned int EXT3_DIRSYNC_FL ; 
 TYPE_1__* EXT3_I (struct inode*) ; 
 unsigned int EXT3_IMMUTABLE_FL ; 
 unsigned int EXT3_NOATIME_FL ; 
 unsigned int EXT3_SYNC_FL ; 
 int S_APPEND ; 
 int S_DIRSYNC ; 
 int S_IMMUTABLE ; 
 int S_NOATIME ; 
 int S_SYNC ; 

void ext3_set_inode_flags(struct inode *inode)
{
	unsigned int flags = EXT3_I(inode)->i_flags;

	inode->i_flags &= ~(S_SYNC|S_APPEND|S_IMMUTABLE|S_NOATIME|S_DIRSYNC);
	if (flags & EXT3_SYNC_FL)
		inode->i_flags |= S_SYNC;
	if (flags & EXT3_APPEND_FL)
		inode->i_flags |= S_APPEND;
	if (flags & EXT3_IMMUTABLE_FL)
		inode->i_flags |= S_IMMUTABLE;
	if (flags & EXT3_NOATIME_FL)
		inode->i_flags |= S_NOATIME;
	if (flags & EXT3_DIRSYNC_FL)
		inode->i_flags |= S_DIRSYNC;
}