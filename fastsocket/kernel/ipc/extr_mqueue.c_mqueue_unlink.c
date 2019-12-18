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
struct inode {int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
 scalar_t__ DIRENT_SIZE ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 

__attribute__((used)) static int mqueue_unlink(struct inode *dir, struct dentry *dentry)
{
  	struct inode *inode = dentry->d_inode;

	dir->i_ctime = dir->i_mtime = dir->i_atime = CURRENT_TIME;
	dir->i_size -= DIRENT_SIZE;
  	drop_nlink(inode);
  	dput(dentry);
  	return 0;
}