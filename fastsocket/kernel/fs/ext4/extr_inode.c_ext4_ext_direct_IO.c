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
struct kiocb {int /*<<< orphan*/ * private; struct file* ki_filp; } ;
struct iovec {int dummy; } ;
struct inode {scalar_t__ i_size; TYPE_2__* i_sb; } ;
struct file {TYPE_1__* f_mapping; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_6__ {int /*<<< orphan*/ * cur_aio_dio; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_bdev; } ;
struct TYPE_4__ {struct inode* host; } ;

/* Variables and functions */
 int EIOCBQUEUED ; 
 int ENOMEM ; 
 TYPE_3__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_STATE_DIO_UNWRITTEN ; 
 int WRITE ; 
 int blockdev_direct_IO (int,struct kiocb*,struct inode*,int /*<<< orphan*/ ,struct iovec const*,scalar_t__,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_clear_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_convert_unwritten_extents (struct inode*,scalar_t__,int) ; 
 int /*<<< orphan*/  ext4_end_io_dio ; 
 int /*<<< orphan*/  ext4_free_io_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_get_block_dio_write ; 
 int ext4_ind_direct_IO (int,struct kiocb*,struct iovec const*,scalar_t__,unsigned long) ; 
 int /*<<< orphan*/ * ext4_init_io_end (struct inode*) ; 
 scalar_t__ ext4_test_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 size_t iov_length (struct iovec const*,unsigned long) ; 
 int /*<<< orphan*/  is_sync_kiocb (struct kiocb*) ; 

__attribute__((used)) static ssize_t ext4_ext_direct_IO(int rw, struct kiocb *iocb,
			      const struct iovec *iov, loff_t offset,
			      unsigned long nr_segs)
{
	struct file *file = iocb->ki_filp;
	struct inode *inode = file->f_mapping->host;
	ssize_t ret;
	size_t count = iov_length(iov, nr_segs);

	loff_t final_size = offset + count;
	if (rw == WRITE && final_size <= inode->i_size) {
		/*
 		 * We could direct write to holes and fallocate.
		 *
 		 * Allocated blocks to fill the hole are marked as uninitialized
 		 * to prevent paralel buffered read to expose the stale data
 		 * before DIO complete the data IO.
		 *
 		 * As to previously fallocated extents, ext4 get_block
 		 * will just simply mark the buffer mapped but still
 		 * keep the extents uninitialized.
 		 *
		 * for non AIO case, we will convert those unwritten extents
		 * to written after return back from blockdev_direct_IO.
		 *
		 * for async DIO, the conversion needs to be defered when
		 * the IO is completed. The ext4 end_io callback function
		 * will be called to take care of the conversion work.
		 * Here for async case, we allocate an io_end structure to
		 * hook to the iocb.
 		 */
		iocb->private = NULL;
		EXT4_I(inode)->cur_aio_dio = NULL;
		if (!is_sync_kiocb(iocb)) {
			iocb->private = ext4_init_io_end(inode);
			if (!iocb->private)
				return -ENOMEM;
			/*
			 * we save the io structure for current async
			 * direct IO, so that later ext4_get_blocks()
			 * could flag the io structure whether there
			 * is a unwritten extents needs to be converted
			 * when IO is completed.
			 */
			EXT4_I(inode)->cur_aio_dio = iocb->private;
		}

		ret = blockdev_direct_IO(rw, iocb, inode,
					 inode->i_sb->s_bdev, iov,
					 offset, nr_segs,
					 ext4_get_block_dio_write,
					 ext4_end_io_dio);
		if (iocb->private)
			EXT4_I(inode)->cur_aio_dio = NULL;
		/*
		 * The io_end structure takes a reference to the inode,
		 * that structure needs to be destroyed and the
		 * reference to the inode need to be dropped, when IO is
		 * complete, even with 0 byte write, or failed.
		 *
		 * In the successful AIO DIO case, the io_end structure will be
		 * desctroyed and the reference to the inode will be dropped
		 * after the end_io call back function is called.
		 *
		 * In the case there is 0 byte write, or error case, since
		 * VFS direct IO won't invoke the end_io call back function,
		 * we need to free the end_io structure here.
		 */
		if (ret != -EIOCBQUEUED && ret <= 0 && iocb->private) {
			ext4_free_io_end(iocb->private);
			iocb->private = NULL;
		} else if (ret > 0 && ext4_test_inode_state(inode,
						EXT4_STATE_DIO_UNWRITTEN)) {
			int err;
			/*
			 * for non AIO case, since the IO is already
			 * completed, we could do the convertion right here
			 */
			err = ext4_convert_unwritten_extents(inode,
							     offset, ret);
			if (err < 0)
				ret = err;
			ext4_clear_inode_state(inode, EXT4_STATE_DIO_UNWRITTEN);
		}
		return ret;
	}

	/* for write the the end of file case, we fall back to old way */
	return ext4_ind_direct_IO(rw, iocb, iov, offset, nr_segs);
}