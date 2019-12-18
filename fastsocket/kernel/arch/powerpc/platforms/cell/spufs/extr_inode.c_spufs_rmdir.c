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
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int simple_rmdir (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  spufs_prune_dir (struct dentry*) ; 

__attribute__((used)) static int spufs_rmdir(struct inode *parent, struct dentry *dir)
{
	/* remove all entries */
	spufs_prune_dir(dir);
	d_drop(dir);

	return simple_rmdir(parent, dir);
}