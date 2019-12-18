#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct dentry* dentry; } ;
struct file {int /*<<< orphan*/  f_pos; TYPE_1__ f_path; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  filldir_t ;

/* Variables and functions */
 int reiserfs_readdir_dentry (struct dentry*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int reiserfs_readdir(struct file *file, void *dirent, filldir_t filldir)
{
	struct dentry *dentry = file->f_path.dentry;
	return reiserfs_readdir_dentry(dentry, dirent, filldir, &file->f_pos);
}