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
struct kstatfs {scalar_t__ f_frsize; scalar_t__ f_bsize; } ;
struct dentry {TYPE_2__* d_sb; } ;
struct TYPE_4__ {TYPE_1__* s_op; } ;
struct TYPE_3__ {int (* statfs ) (struct dentry*,struct kstatfs*) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  memset (struct kstatfs*,int /*<<< orphan*/ ,int) ; 
 int security_sb_statfs (struct dentry*) ; 
 int stub1 (struct dentry*,struct kstatfs*) ; 

int statfs_by_dentry(struct dentry *dentry, struct kstatfs *buf)
{
	int retval;

	if (!dentry->d_sb->s_op->statfs)
		return -ENOSYS;

	memset(buf, 0, sizeof(*buf));
	retval = security_sb_statfs(dentry);
	if (retval)
		return retval;
	retval = dentry->d_sb->s_op->statfs(dentry, buf);
	if (retval == 0 && buf->f_frsize == 0)
		buf->f_frsize = buf->f_bsize;
	return retval;
}