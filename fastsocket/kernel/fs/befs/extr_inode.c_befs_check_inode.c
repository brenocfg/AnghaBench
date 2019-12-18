#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct super_block {int dummy; } ;
typedef  int /*<<< orphan*/  befs_inode_addr ;
struct TYPE_3__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  inode_num; int /*<<< orphan*/  magic1; } ;
typedef  TYPE_1__ befs_inode ;
typedef  scalar_t__ befs_blocknr_t ;

/* Variables and functions */
 int BEFS_BAD_INODE ; 
 scalar_t__ BEFS_INODE_IN_USE ; 
 scalar_t__ BEFS_INODE_MAGIC1 ; 
 int BEFS_OK ; 
 int /*<<< orphan*/  befs_error (struct super_block*,char*,scalar_t__,...) ; 
 scalar_t__ fs32_to_cpu (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsrun_to_cpu (struct super_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ iaddr2blockno (struct super_block*,int /*<<< orphan*/ *) ; 

int
befs_check_inode(struct super_block *sb, befs_inode * raw_inode,
		 befs_blocknr_t inode)
{
	u32 magic1 = fs32_to_cpu(sb, raw_inode->magic1);
	befs_inode_addr ino_num = fsrun_to_cpu(sb, raw_inode->inode_num);
	u32 flags = fs32_to_cpu(sb, raw_inode->flags);

	/* check magic header. */
	if (magic1 != BEFS_INODE_MAGIC1) {
		befs_error(sb,
			   "Inode has a bad magic header - inode = %lu", inode);
		return BEFS_BAD_INODE;
	}

	/*
	 * Sanity check2: inodes store their own block address. Check it.
	 */
	if (inode != iaddr2blockno(sb, &ino_num)) {
		befs_error(sb, "inode blocknr field disagrees with vfs "
			   "VFS: %lu, Inode %lu",
			   inode, iaddr2blockno(sb, &ino_num));
		return BEFS_BAD_INODE;
	}

	/*
	 * check flag
	 */

	if (!(flags & BEFS_INODE_IN_USE)) {
		befs_error(sb, "inode is not used - inode = %lu", inode);
		return BEFS_BAD_INODE;
	}

	return BEFS_OK;
}