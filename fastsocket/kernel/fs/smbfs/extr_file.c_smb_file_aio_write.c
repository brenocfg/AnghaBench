#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct kiocb {scalar_t__ ki_left; struct file* ki_filp; } ;
struct iovec {int dummy; } ;
struct TYPE_5__ {struct dentry* dentry; } ;
struct file {scalar_t__ f_pos; TYPE_1__ f_path; } ;
struct dentry {TYPE_4__* d_inode; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_7__ {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_6__ {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_8__ {TYPE_3__ i_atime; TYPE_2__ i_mtime; scalar_t__ i_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DENTRY_PATH (struct dentry*) ; 
 int /*<<< orphan*/  PARANOIA (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SMB_O_WRONLY ; 
 int /*<<< orphan*/  VERBOSE (char*,long,long,unsigned long,...) ; 
 scalar_t__ generic_file_aio_write (struct kiocb*,struct iovec const*,unsigned long,scalar_t__) ; 
 scalar_t__ smb_open (struct dentry*,int /*<<< orphan*/ ) ; 
 scalar_t__ smb_revalidate_inode (struct dentry*) ; 

__attribute__((used)) static ssize_t
smb_file_aio_write(struct kiocb *iocb, const struct iovec *iov,
			       unsigned long nr_segs, loff_t pos)
{
	struct file * file = iocb->ki_filp;
	struct dentry * dentry = file->f_path.dentry;
	ssize_t	result;

	VERBOSE("file %s/%s, count=%lu@%lu\n",
		DENTRY_PATH(dentry),
		(unsigned long) iocb->ki_left, (unsigned long) pos);

	result = smb_revalidate_inode(dentry);
	if (result) {
		PARANOIA("%s/%s validation failed, error=%Zd\n",
			 DENTRY_PATH(dentry), result);
		goto out;
	}

	result = smb_open(dentry, SMB_O_WRONLY);
	if (result)
		goto out;

	if (iocb->ki_left > 0) {
		result = generic_file_aio_write(iocb, iov, nr_segs, pos);
		VERBOSE("pos=%ld, size=%ld, mtime=%ld, atime=%ld\n",
			(long) file->f_pos, (long) dentry->d_inode->i_size,
			dentry->d_inode->i_mtime.tv_sec,
			dentry->d_inode->i_atime.tv_sec);
	}
out:
	return result;
}