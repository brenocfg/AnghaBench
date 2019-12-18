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
struct kiocb {TYPE_3__* ki_filp; } ;
struct iovec {int dummy; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_8__ {scalar_t__ clientCanCacheRead; } ;
struct TYPE_6__ {TYPE_1__* dentry; } ;
struct TYPE_7__ {TYPE_2__ f_path; } ;
struct TYPE_5__ {struct inode* d_inode; } ;

/* Variables and functions */
 TYPE_4__* CIFS_I (struct inode*) ; 
 int /*<<< orphan*/  cifs_user_readv (struct kiocb*,struct iovec const*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_file_aio_read (struct kiocb*,struct iovec const*,unsigned long,int /*<<< orphan*/ ) ; 

ssize_t cifs_strict_readv(struct kiocb *iocb, const struct iovec *iov,
			  unsigned long nr_segs, loff_t pos)
{
	struct inode *inode;

	inode = iocb->ki_filp->f_path.dentry->d_inode;

	if (CIFS_I(inode)->clientCanCacheRead)
		return generic_file_aio_read(iocb, iov, nr_segs, pos);

	/*
	 * In strict cache mode we need to read from the server all the time
	 * if we don't have level II oplock because the server can delay mtime
	 * change - so we can't make a decision about inode invalidating.
	 * And we can also fail with pagereading if there are mandatory locks
	 * on pages affected by this read but not on the region from pos to
	 * pos+len-1.
	 */

	return cifs_user_readv(iocb, iov, nr_segs, pos);
}