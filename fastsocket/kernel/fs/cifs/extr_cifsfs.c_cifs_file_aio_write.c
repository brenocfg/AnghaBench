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
struct inode {int /*<<< orphan*/  i_mapping; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_8__ {scalar_t__ clientCanCacheAll; } ;
struct TYPE_6__ {TYPE_1__* dentry; } ;
struct TYPE_7__ {TYPE_2__ f_path; } ;
struct TYPE_5__ {struct inode* d_inode; } ;

/* Variables and functions */
 TYPE_4__* CIFS_I (struct inode*) ; 
 int /*<<< orphan*/  cFYI (int,char*,int,struct inode*) ; 
 int filemap_fdatawrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_file_aio_write (struct kiocb*,struct iovec const*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t cifs_file_aio_write(struct kiocb *iocb, const struct iovec *iov,
				   unsigned long nr_segs, loff_t pos)
{
	struct inode *inode = iocb->ki_filp->f_path.dentry->d_inode;
	ssize_t written;
	int rc;

	written = generic_file_aio_write(iocb, iov, nr_segs, pos);

	if (CIFS_I(inode)->clientCanCacheAll)
		return written;

	rc = filemap_fdatawrite(inode->i_mapping);
	if (rc)
		cFYI(1, "cifs_file_aio_write: %d rc on %p inode", rc, inode);

	return written;
}