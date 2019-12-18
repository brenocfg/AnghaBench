#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_3__ {struct dentry* dentry; } ;
struct file {TYPE_1__ f_path; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dentry {TYPE_2__ d_name; int /*<<< orphan*/  d_sb; } ;
struct autofs_sb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,struct file*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 scalar_t__ autofs4_oz_mode (struct autofs_sb_info*) ; 
 struct autofs_sb_info* autofs4_sbi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_mountpoint (struct dentry*) ; 
 int dcache_dir_open (struct inode*,struct file*) ; 
 scalar_t__ simple_empty (struct dentry*) ; 

__attribute__((used)) static int autofs4_dir_open(struct inode *inode, struct file *file)
{
	struct dentry *dentry = file->f_path.dentry;
	struct autofs_sb_info *sbi = autofs4_sbi(dentry->d_sb);

	DPRINTK("file=%p dentry=%p %.*s",
		file, dentry, dentry->d_name.len, dentry->d_name.name);

	if (autofs4_oz_mode(sbi))
		goto out;

	/*
	 * An empty directory in an autofs file system is always a
	 * mount point. The daemon must have failed to mount this
	 * during lookup so it doesn't exist. This can happen, for
	 * example, if user space returns an incorrect status for a
	 * mount request. Otherwise we're doing a readdir on the
	 * autofs file system so just let the libfs routines handle
	 * it.
	 */
	if (!d_mountpoint(dentry) && simple_empty(dentry))
		return -ENOENT;

out:
	return dcache_dir_open(inode, file);
}