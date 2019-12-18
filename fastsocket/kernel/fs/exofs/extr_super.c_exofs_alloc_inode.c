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
struct exofs_i_info {struct inode vfs_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  exofs_inode_cachep ; 
 struct exofs_i_info* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct inode *exofs_alloc_inode(struct super_block *sb)
{
	struct exofs_i_info *oi;

	oi = kmem_cache_alloc(exofs_inode_cachep, GFP_KERNEL);
	if (!oi)
		return NULL;

	oi->vfs_inode.i_version = 1;
	return &oi->vfs_inode;
}