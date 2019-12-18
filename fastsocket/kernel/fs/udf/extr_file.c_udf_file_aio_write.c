#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct udf_inode_info {scalar_t__ i_alloc_type; int i_lenAlloc; } ;
struct kiocb {size_t ki_left; struct file* ki_filp; } ;
struct iovec {int dummy; } ;
struct inode {int i_size; TYPE_3__* i_sb; } ;
struct TYPE_5__ {TYPE_1__* dentry; } ;
struct file {int f_flags; TYPE_2__ f_path; } ;
typedef  int ssize_t ;
typedef  int loff_t ;
struct TYPE_6__ {scalar_t__ s_blocksize; } ;
struct TYPE_4__ {struct inode* d_inode; } ;

/* Variables and functions */
 scalar_t__ ICBTAG_FLAG_AD_IN_ICB ; 
 int O_APPEND ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int generic_file_aio_write (struct kiocb*,struct iovec const*,unsigned long,int) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  udf_debug (char*,int) ; 
 int /*<<< orphan*/  udf_expand_file_adinicb (struct inode*,int,int*) ; 
 scalar_t__ udf_file_entry_alloc_offset (struct inode*) ; 

__attribute__((used)) static ssize_t udf_file_aio_write(struct kiocb *iocb, const struct iovec *iov,
				  unsigned long nr_segs, loff_t ppos)
{
	ssize_t retval;
	struct file *file = iocb->ki_filp;
	struct inode *inode = file->f_path.dentry->d_inode;
	int err, pos;
	size_t count = iocb->ki_left;
	struct udf_inode_info *iinfo = UDF_I(inode);

	if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB) {
		if (file->f_flags & O_APPEND)
			pos = inode->i_size;
		else
			pos = ppos;

		if (inode->i_sb->s_blocksize <
				(udf_file_entry_alloc_offset(inode) +
						pos + count)) {
			udf_expand_file_adinicb(inode, pos + count, &err);
			if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB) {
				udf_debug("udf_expand_adinicb: err=%d\n", err);
				return err;
			}
		} else {
			if (pos + count > inode->i_size)
				iinfo->i_lenAlloc = pos + count;
			else
				iinfo->i_lenAlloc = inode->i_size;
		}
	}

	retval = generic_file_aio_write(iocb, iov, nr_segs, ppos);
	if (retval > 0)
		mark_inode_dirty(inode);

	return retval;
}