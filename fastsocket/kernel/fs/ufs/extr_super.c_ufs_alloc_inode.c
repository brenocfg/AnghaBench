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
struct inode {int i_version; } ;
struct ufs_inode_info {struct inode vfs_inode; } ;
struct super_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufs_inode_cachep ; 

__attribute__((used)) static struct inode *ufs_alloc_inode(struct super_block *sb)
{
	struct ufs_inode_info *ei;
	ei = (struct ufs_inode_info *)kmem_cache_alloc(ufs_inode_cachep, GFP_KERNEL);
	if (!ei)
		return NULL;
	ei->vfs_inode.i_version = 1;
	return &ei->vfs_inode;
}