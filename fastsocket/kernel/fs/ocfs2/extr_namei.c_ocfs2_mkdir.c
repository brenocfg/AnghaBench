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
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dentry {TYPE_1__ d_name; } ;

/* Variables and functions */
 int S_IFDIR ; 
 int /*<<< orphan*/  mlog_entry (char*,struct inode*,struct dentry*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_mknod (struct inode*,struct dentry*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_mkdir(struct inode *dir,
		       struct dentry *dentry,
		       int mode)
{
	int ret;

	mlog_entry("(0x%p, 0x%p, %d, '%.*s')\n", dir, dentry, mode,
		   dentry->d_name.len, dentry->d_name.name);
	ret = ocfs2_mknod(dir, dentry, mode | S_IFDIR, 0);
	mlog_exit(ret);

	return ret;
}