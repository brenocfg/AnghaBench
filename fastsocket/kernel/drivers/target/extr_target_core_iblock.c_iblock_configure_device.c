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
struct TYPE_4__ {int max_unmap_block_desc_count; int unmap_granularity; int max_write_same_len; int is_nonrot; int /*<<< orphan*/  unmap_granularity_alignment; int /*<<< orphan*/  max_unmap_lba_count; int /*<<< orphan*/  hw_queue_depth; int /*<<< orphan*/  hw_max_sectors; int /*<<< orphan*/  hw_block_size; } ;
struct se_device {TYPE_2__ dev_attrib; } ;
struct TYPE_3__ {int discard_granularity; int /*<<< orphan*/  discard_alignment; int /*<<< orphan*/  max_discard_sectors; } ;
struct request_queue {TYPE_1__ limits; int /*<<< orphan*/  nr_requests; } ;
struct iblock_dev {int ibd_flags; int /*<<< orphan*/ * ibd_bio_set; struct block_device* ibd_bd; int /*<<< orphan*/  ibd_udev_path; int /*<<< orphan*/  ibd_readonly; } ;
struct block_device {int dummy; } ;
typedef  int fmode_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int FMODE_EXCL ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int IBDF_HAS_UDEV_PATH ; 
 int /*<<< orphan*/  IBLOCK_BIO_POOL_SIZE ; 
 struct iblock_dev* IBLOCK_DEV (struct se_device*) ; 
 scalar_t__ IS_ERR (struct block_device*) ; 
 int PTR_ERR (struct block_device*) ; 
 int /*<<< orphan*/  UINT_MAX ; 
 struct request_queue* bdev_get_queue (struct block_device*) ; 
 int /*<<< orphan*/  bdev_logical_block_size (struct block_device*) ; 
 int /*<<< orphan*/ * bioset_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bioset_free (int /*<<< orphan*/ *) ; 
 scalar_t__ blk_queue_discard (struct request_queue*) ; 
 scalar_t__ blk_queue_nonrot (struct request_queue*) ; 
 struct block_device* open_bdev_exclusive (int /*<<< orphan*/ ,int,struct iblock_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int iblock_configure_device(struct se_device *dev)
{
	struct iblock_dev *ib_dev = IBLOCK_DEV(dev);
	struct request_queue *q;
	struct block_device *bd = NULL;
	fmode_t mode;
	int ret = -ENOMEM;

	if (!(ib_dev->ibd_flags & IBDF_HAS_UDEV_PATH)) {
		pr_err("Missing udev_path= parameters for IBLOCK\n");
		return -EINVAL;
	}

	ib_dev->ibd_bio_set = bioset_create(IBLOCK_BIO_POOL_SIZE, 0);
	if (!ib_dev->ibd_bio_set) {
		pr_err("IBLOCK: Unable to create bioset\n");
		goto out;
	}

	pr_debug( "IBLOCK: Claiming struct block_device: %s\n",
			ib_dev->ibd_udev_path);

	mode = FMODE_READ|FMODE_EXCL;
	if (!ib_dev->ibd_readonly)
		mode |= FMODE_WRITE;

	bd = open_bdev_exclusive(ib_dev->ibd_udev_path, mode, ib_dev);
	if (IS_ERR(bd)) {
		ret = PTR_ERR(bd);
		goto out_free_bioset;
	}
	ib_dev->ibd_bd = bd;

	q = bdev_get_queue(bd);

	dev->dev_attrib.hw_block_size = bdev_logical_block_size(bd);
	dev->dev_attrib.hw_max_sectors = UINT_MAX;
	dev->dev_attrib.hw_queue_depth = q->nr_requests;

	/*
	 * Check if the underlying struct block_device request_queue supports
	 * the QUEUE_FLAG_DISCARD bit for UNMAP/WRITE_SAME in SCSI + TRIM
	 * in ATA and we need to set TPE=1
	 */
	if (blk_queue_discard(q)) {
		dev->dev_attrib.max_unmap_lba_count =
				q->limits.max_discard_sectors;

		/*
		 * Currently hardcoded to 1 in Linux/SCSI code..
		 */
		dev->dev_attrib.max_unmap_block_desc_count = 1;
		dev->dev_attrib.unmap_granularity =
				q->limits.discard_granularity >> 9;
		dev->dev_attrib.unmap_granularity_alignment =
				q->limits.discard_alignment;

		pr_debug("IBLOCK: BLOCK Discard support available,"
				" disabled by default\n");
	}
	/*
	 * Enable write same emulation for IBLOCK and use 0xFFFF as
	 * the smaller WRITE_SAME(10) only has a two-byte block count.
	 */
	dev->dev_attrib.max_write_same_len = 0xFFFF;

	if (blk_queue_nonrot(q))
		dev->dev_attrib.is_nonrot = 1;

	return 0;

out_free_bioset:
	bioset_free(ib_dev->ibd_bio_set);
	ib_dev->ibd_bio_set = NULL;
out:
	return ret;
}