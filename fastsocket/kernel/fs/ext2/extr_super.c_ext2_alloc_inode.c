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
struct super_block {int dummy; } ;
struct inode {int i_version; } ;
struct ext2_inode_info {struct inode vfs_inode; int /*<<< orphan*/ * i_block_alloc_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ext2_inode_cachep ; 
 scalar_t__ kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct inode *ext2_alloc_inode(struct super_block *sb)
{
	struct ext2_inode_info *ei;
	ei = (struct ext2_inode_info *)kmem_cache_alloc(ext2_inode_cachep, GFP_KERNEL);
	if (!ei)
		return NULL;
	ei->i_block_alloc_info = NULL;
	ei->vfs_inode.i_version = 1;
	return &ei->vfs_inode;
}