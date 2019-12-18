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
struct nameidata {int dummy; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* ERR_CAST (struct inode*) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 struct inode* btrfs_lookup_dentry (struct inode*,struct dentry*) ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 

__attribute__((used)) static struct dentry *btrfs_lookup(struct inode *dir, struct dentry *dentry,
				   struct nameidata *nd)
{
	struct inode *inode;

	inode = btrfs_lookup_dentry(dir, dentry);
	if (IS_ERR(inode))
		return ERR_CAST(inode);

	return d_splice_alias(inode, dentry);
}