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
struct TYPE_2__ {unsigned int flags; } ;

/* Variables and functions */
 int S_APPEND ; 
 int S_DIRSYNC ; 
 int S_IMMUTABLE ; 
 int S_SYNC ; 
 unsigned int UBIFS_APPEND_FL ; 
 unsigned int UBIFS_DIRSYNC_FL ; 
 unsigned int UBIFS_IMMUTABLE_FL ; 
 unsigned int UBIFS_SYNC_FL ; 
 TYPE_1__* ubifs_inode (struct inode*) ; 

void ubifs_set_inode_flags(struct inode *inode)
{
	unsigned int flags = ubifs_inode(inode)->flags;

	inode->i_flags &= ~(S_SYNC | S_APPEND | S_IMMUTABLE | S_DIRSYNC);
	if (flags & UBIFS_SYNC_FL)
		inode->i_flags |= S_SYNC;
	if (flags & UBIFS_APPEND_FL)
		inode->i_flags |= S_APPEND;
	if (flags & UBIFS_IMMUTABLE_FL)
		inode->i_flags |= S_IMMUTABLE;
	if (flags & UBIFS_DIRSYNC_FL)
		inode->i_flags |= S_DIRSYNC;
}