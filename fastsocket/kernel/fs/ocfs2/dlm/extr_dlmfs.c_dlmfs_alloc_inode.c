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
struct inode {int dummy; } ;
struct dlmfs_inode_private {struct inode ip_vfs_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  dlmfs_inode_cache ; 
 struct dlmfs_inode_private* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct inode *dlmfs_alloc_inode(struct super_block *sb)
{
	struct dlmfs_inode_private *ip;

	ip = kmem_cache_alloc(dlmfs_inode_cache, GFP_NOFS);
	if (!ip)
		return NULL;

	return &ip->ip_vfs_inode;
}