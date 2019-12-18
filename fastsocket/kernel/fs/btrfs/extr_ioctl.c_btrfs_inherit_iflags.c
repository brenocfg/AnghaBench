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
struct inode {int dummy; } ;
struct TYPE_2__ {unsigned int flags; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 unsigned int BTRFS_INODE_COMPRESS ; 
 unsigned int BTRFS_INODE_NOCOMPRESS ; 
 unsigned int BTRFS_INODE_NODATACOW ; 
 int /*<<< orphan*/  btrfs_update_iflags (struct inode*) ; 

void btrfs_inherit_iflags(struct inode *inode, struct inode *dir)
{
	unsigned int flags;

	if (!dir)
		return;

	flags = BTRFS_I(dir)->flags;

	if (flags & BTRFS_INODE_NOCOMPRESS) {
		BTRFS_I(inode)->flags &= ~BTRFS_INODE_COMPRESS;
		BTRFS_I(inode)->flags |= BTRFS_INODE_NOCOMPRESS;
	} else if (flags & BTRFS_INODE_COMPRESS) {
		BTRFS_I(inode)->flags &= ~BTRFS_INODE_NOCOMPRESS;
		BTRFS_I(inode)->flags |= BTRFS_INODE_COMPRESS;
	}

	if (flags & BTRFS_INODE_NODATACOW)
		BTRFS_I(inode)->flags |= BTRFS_INODE_NODATACOW;

	btrfs_update_iflags(inode);
}