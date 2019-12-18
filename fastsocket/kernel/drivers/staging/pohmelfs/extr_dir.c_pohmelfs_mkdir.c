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
struct dentry {int dummy; } ;

/* Variables and functions */
 int S_IFDIR ; 
 int /*<<< orphan*/  inode_dec_link_count (struct inode*) ; 
 int /*<<< orphan*/  inode_inc_link_count (struct inode*) ; 
 int pohmelfs_create_entry (struct inode*,struct dentry*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pohmelfs_mkdir(struct inode *dir, struct dentry *dentry, int mode)
{
	int err;

	inode_inc_link_count(dir);
	err = pohmelfs_create_entry(dir, dentry, 0, mode | S_IFDIR);
	if (err)
		inode_dec_link_count(dir);

	return err;
}