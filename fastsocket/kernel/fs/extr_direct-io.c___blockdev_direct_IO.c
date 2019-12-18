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
struct kiocb {int dummy; } ;
struct iovec {int dummy; } ;
struct inode {int dummy; } ;
struct block_device {TYPE_1__* bd_disk; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  get_block_t ;
typedef  int /*<<< orphan*/  dio_submit_t ;
typedef  int /*<<< orphan*/  dio_iodone_t ;
struct TYPE_2__ {char part_tbl; char* queue; } ;

/* Variables and functions */
 int SMP_CACHE_BYTES ; 
 int /*<<< orphan*/  do_blockdev_direct_IO (int,struct kiocb*,struct inode*,struct block_device*,struct iovec const*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prefetch (char*) ; 

ssize_t
__blockdev_direct_IO(int rw, struct kiocb *iocb, struct inode *inode,
	struct block_device *bdev, const struct iovec *iov, loff_t offset,
	unsigned long nr_segs, get_block_t get_block, dio_iodone_t end_io,
	dio_submit_t submit_io,	int flags)
{
	/*
	 * The block device state is needed in the end to finally
	 * submit everything.  Since it's likely to be cache cold
	 * prefetch it here as first thing to hide some of the
	 * latency.
	 *
	 * Attempt to prefetch the pieces we likely need later.
	 */
	prefetch(&bdev->bd_disk->part_tbl);
	prefetch(bdev->bd_disk->queue);
	prefetch((char *)bdev->bd_disk->queue + SMP_CACHE_BYTES);

	return do_blockdev_direct_IO(rw, iocb, inode, bdev, iov, offset,
				     nr_segs, get_block, end_io,
				     submit_io, flags);
}