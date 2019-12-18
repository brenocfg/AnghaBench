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
struct hppfs_inode_info {struct inode vfs_inode; int /*<<< orphan*/ * proc_dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  inode_init_once (struct inode*) ; 
 struct hppfs_inode_info* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct inode *hppfs_alloc_inode(struct super_block *sb)
{
	struct hppfs_inode_info *hi;

	hi = kmalloc(sizeof(*hi), GFP_KERNEL);
	if (!hi)
		return NULL;

	hi->proc_dentry = NULL;
	inode_init_once(&hi->vfs_inode);
	return &hi->vfs_inode;
}