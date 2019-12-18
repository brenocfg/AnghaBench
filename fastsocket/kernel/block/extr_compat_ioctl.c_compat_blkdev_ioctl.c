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
struct inode {struct block_device* i_bdev; } ;
struct gendisk {TYPE_2__* fops; } ;
struct file {int f_flags; int /*<<< orphan*/  f_mode; TYPE_1__* f_mapping; } ;
struct block_device {int /*<<< orphan*/  bd_inode; struct gendisk* bd_disk; } ;
struct backing_dev_info {int ra_pages; } ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_4__ {int (* compat_ioctl ) (struct block_device*,int /*<<< orphan*/ ,unsigned int,unsigned long) ;} ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
#define  BLKALIGNOFF 153 
#define  BLKBSZGET_32 152 
 unsigned int BLKBSZSET ; 
#define  BLKBSZSET_32 151 
#define  BLKDISCARD 150 
#define  BLKDISCARDZEROES 149 
#define  BLKFLSBUF 148 
#define  BLKFRAGET 147 
#define  BLKFRASET 146 
#define  BLKGETSIZE 145 
#define  BLKGETSIZE64_32 144 
#define  BLKIOMIN 143 
#define  BLKIOOPT 142 
#define  BLKPBSZGET 141 
#define  BLKPG 140 
#define  BLKRAGET 139 
#define  BLKRASET 138 
#define  BLKROGET 137 
#define  BLKROSET 136 
#define  BLKRRPART 135 
#define  BLKSECTGET 134 
#define  BLKSSZGET 133 
#define  BLKTRACESETUP32 132 
#define  BLKTRACESTART 131 
#define  BLKTRACESTOP 130 
#define  BLKTRACETEARDOWN 129 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 long EACCES ; 
 long EFBIG ; 
 long EINVAL ; 
 int ENOIOCTLCMD ; 
 long ENOTTY ; 
 int /*<<< orphan*/  FMODE_NDELAY ; 
#define  HDIO_GETGEO 128 
 int O_NDELAY ; 
 int PAGE_CACHE_SIZE ; 
 int bdev_alignment_offset (struct block_device*) ; 
 int /*<<< orphan*/  bdev_discard_zeroes_data (struct block_device*) ; 
 int /*<<< orphan*/  bdev_get_queue (struct block_device*) ; 
 int /*<<< orphan*/  bdev_io_min (struct block_device*) ; 
 int /*<<< orphan*/  bdev_io_opt (struct block_device*) ; 
 int bdev_logical_block_size (struct block_device*) ; 
 int /*<<< orphan*/  bdev_physical_block_size (struct block_device*) ; 
 int /*<<< orphan*/  bdev_read_only (struct block_device*) ; 
 struct backing_dev_info* blk_get_backing_dev_info (struct block_device*) ; 
 int blk_trace_ioctl (struct block_device*,unsigned int,scalar_t__) ; 
 long blkdev_ioctl (struct block_device*,int /*<<< orphan*/ ,unsigned int,unsigned long) ; 
 int block_size (struct block_device*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int compat_blk_trace_setup (struct block_device*,scalar_t__) ; 
 int compat_blkdev_driver_ioctl (struct block_device*,int /*<<< orphan*/ ,unsigned int,unsigned long) ; 
 long compat_blkpg_ioctl (struct block_device*,int /*<<< orphan*/ ,unsigned int,scalar_t__) ; 
 long compat_hdio_getgeo (struct gendisk*,struct block_device*,scalar_t__) ; 
 scalar_t__ compat_ptr (unsigned long) ; 
 long compat_put_int (unsigned long,int) ; 
 long compat_put_long (unsigned long,int) ; 
 long compat_put_u64 (unsigned long,int) ; 
 long compat_put_uint (unsigned long,int /*<<< orphan*/ ) ; 
 long compat_put_ulong (unsigned long,int) ; 
 long compat_put_ushort (unsigned long,int /*<<< orphan*/ ) ; 
 int i_size_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  queue_max_sectors (int /*<<< orphan*/ ) ; 
 int stub1 (struct block_device*,int /*<<< orphan*/ ,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

long compat_blkdev_ioctl(struct file *file, unsigned cmd, unsigned long arg)
{
	int ret = -ENOIOCTLCMD;
	struct inode *inode = file->f_mapping->host;
	struct block_device *bdev = inode->i_bdev;
	struct gendisk *disk = bdev->bd_disk;
	fmode_t mode = file->f_mode;
	struct backing_dev_info *bdi;
	loff_t size;

	/*
	 * O_NDELAY can be altered using fcntl(.., F_SETFL, ..), so we have
	 * to updated it before every ioctl.
	 */
	if (file->f_flags & O_NDELAY)
		mode |= FMODE_NDELAY;
	else
		mode &= ~FMODE_NDELAY;

	switch (cmd) {
	case HDIO_GETGEO:
		return compat_hdio_getgeo(disk, bdev, compat_ptr(arg));
	case BLKPBSZGET:
		return compat_put_uint(arg, bdev_physical_block_size(bdev));
	case BLKIOMIN:
		return compat_put_uint(arg, bdev_io_min(bdev));
	case BLKIOOPT:
		return compat_put_uint(arg, bdev_io_opt(bdev));
	case BLKALIGNOFF:
		return compat_put_int(arg, bdev_alignment_offset(bdev));
	case BLKDISCARDZEROES:
		return compat_put_uint(arg, bdev_discard_zeroes_data(bdev));
	case BLKFLSBUF:
	case BLKROSET:
	case BLKDISCARD:
	/*
	 * the ones below are implemented in blkdev_locked_ioctl,
	 * but we call blkdev_ioctl, which gets the lock for us
	 */
	case BLKRRPART:
		return blkdev_ioctl(bdev, mode, cmd,
				(unsigned long)compat_ptr(arg));
	case BLKBSZSET_32:
		return blkdev_ioctl(bdev, mode, BLKBSZSET,
				(unsigned long)compat_ptr(arg));
	case BLKPG:
		return compat_blkpg_ioctl(bdev, mode, cmd, compat_ptr(arg));
	case BLKRAGET:
	case BLKFRAGET:
		if (!arg)
			return -EINVAL;
		bdi = blk_get_backing_dev_info(bdev);
		if (bdi == NULL)
			return -ENOTTY;
		return compat_put_long(arg,
				       (bdi->ra_pages * PAGE_CACHE_SIZE) / 512);
	case BLKROGET: /* compatible */
		return compat_put_int(arg, bdev_read_only(bdev) != 0);
	case BLKBSZGET_32: /* get the logical block size (cf. BLKSSZGET) */
		return compat_put_int(arg, block_size(bdev));
	case BLKSSZGET: /* get block device hardware sector size */
		return compat_put_int(arg, bdev_logical_block_size(bdev));
	case BLKSECTGET:
		return compat_put_ushort(arg,
					 queue_max_sectors(bdev_get_queue(bdev)));
	case BLKRASET: /* compatible, but no compat_ptr (!) */
	case BLKFRASET:
		if (!capable(CAP_SYS_ADMIN))
			return -EACCES;
		bdi = blk_get_backing_dev_info(bdev);
		if (bdi == NULL)
			return -ENOTTY;
		bdi->ra_pages = (arg * 512) / PAGE_CACHE_SIZE;
		return 0;
	case BLKGETSIZE:
		size = i_size_read(bdev->bd_inode);
		if ((size >> 9) > ~0UL)
			return -EFBIG;
		return compat_put_ulong(arg, size >> 9);

	case BLKGETSIZE64_32:
		return compat_put_u64(arg, i_size_read(bdev->bd_inode));

	case BLKTRACESETUP32:
		lock_kernel();
		ret = compat_blk_trace_setup(bdev, compat_ptr(arg));
		unlock_kernel();
		return ret;
	case BLKTRACESTART: /* compatible */
	case BLKTRACESTOP:  /* compatible */
	case BLKTRACETEARDOWN: /* compatible */
		lock_kernel();
		ret = blk_trace_ioctl(bdev, cmd, compat_ptr(arg));
		unlock_kernel();
		return ret;
	default:
		if (disk->fops->compat_ioctl)
			ret = disk->fops->compat_ioctl(bdev, mode, cmd, arg);
		if (ret == -ENOIOCTLCMD)
			ret = compat_blkdev_driver_ioctl(bdev, mode, cmd, arg);
		return ret;
	}
}