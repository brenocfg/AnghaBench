#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct kiocb {scalar_t__ ki_pos; struct file* ki_filp; } ;
struct iovec {int dummy; } ;
struct TYPE_10__ {TYPE_4__* dentry; } ;
struct file {TYPE_5__ f_path; struct address_space* f_mapping; } ;
struct address_space {int /*<<< orphan*/  host; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {TYPE_3__ d_name; TYPE_2__* d_parent; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_1__ d_name; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  FILE ; 
 int /*<<< orphan*/  NFSIOS_DIRECTREADBYTES ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,long long) ; 
 size_t iov_length (struct iovec const*,unsigned long) ; 
 int /*<<< orphan*/  nfs_add_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ nfs_direct_read (struct kiocb*,struct iovec const*,unsigned long,scalar_t__) ; 
 scalar_t__ nfs_sync_mapping (struct address_space*) ; 

ssize_t nfs_file_direct_read(struct kiocb *iocb, const struct iovec *iov,
				unsigned long nr_segs, loff_t pos)
{
	ssize_t retval = -EINVAL;
	struct file *file = iocb->ki_filp;
	struct address_space *mapping = file->f_mapping;
	size_t count;

	count = iov_length(iov, nr_segs);
	nfs_add_stats(mapping->host, NFSIOS_DIRECTREADBYTES, count);

	dfprintk(FILE, "NFS: direct read(%s/%s, %zd@%Ld)\n",
		file->f_path.dentry->d_parent->d_name.name,
		file->f_path.dentry->d_name.name,
		count, (long long) pos);

	retval = 0;
	if (!count)
		goto out;

	retval = nfs_sync_mapping(mapping);
	if (retval)
		goto out;

	retval = nfs_direct_read(iocb, iov, nr_segs, pos);
	if (retval > 0)
		iocb->ki_pos = pos + retval;

out:
	return retval;
}