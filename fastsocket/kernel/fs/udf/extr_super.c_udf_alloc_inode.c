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
struct udf_inode_info {struct inode vfs_inode; scalar_t__ i_strat4096; scalar_t__ i_next_alloc_goal; scalar_t__ i_next_alloc_block; scalar_t__ i_lenExtents; scalar_t__ i_unique; } ;
struct super_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct udf_inode_info* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_inode_cachep ; 

__attribute__((used)) static struct inode *udf_alloc_inode(struct super_block *sb)
{
	struct udf_inode_info *ei;
	ei = kmem_cache_alloc(udf_inode_cachep, GFP_KERNEL);
	if (!ei)
		return NULL;

	ei->i_unique = 0;
	ei->i_lenExtents = 0;
	ei->i_next_alloc_block = 0;
	ei->i_next_alloc_goal = 0;
	ei->i_strat4096 = 0;

	return &ei->vfs_inode;
}