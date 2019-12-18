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
struct inode {int dummy; } ;
struct btrfs_inode {int flags; } ;

/* Variables and functions */
 struct btrfs_inode* BTRFS_I (struct inode*) ; 
 int BTRFS_INODE_COMPRESS ; 
 int BTRFS_INODE_NOCOMPRESS ; 
 int BTRFS_INODE_NODATACOW ; 

__attribute__((used)) static void fixup_inode_flags(struct inode *dir, struct inode *inode)
{
	struct btrfs_inode *b_dir = BTRFS_I(dir);
	struct btrfs_inode *b_inode = BTRFS_I(inode);

	if (b_dir->flags & BTRFS_INODE_NODATACOW)
		b_inode->flags |= BTRFS_INODE_NODATACOW;
	else
		b_inode->flags &= ~BTRFS_INODE_NODATACOW;

	if (b_dir->flags & BTRFS_INODE_COMPRESS) {
		b_inode->flags |= BTRFS_INODE_COMPRESS;
		b_inode->flags &= ~BTRFS_INODE_NOCOMPRESS;
	} else {
		b_inode->flags &= ~(BTRFS_INODE_COMPRESS |
				    BTRFS_INODE_NOCOMPRESS);
	}
}