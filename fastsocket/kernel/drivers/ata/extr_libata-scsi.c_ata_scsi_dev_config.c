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
struct scsi_device {scalar_t__ sector_size; int manage_start_stop; TYPE_1__* host; int /*<<< orphan*/  supported_events; struct request_queue* request_queue; } ;
struct request_queue {int bounce_gfp; } ;
struct ata_device {int flags; scalar_t__ class; struct scsi_device* sdev; int /*<<< orphan*/  id; int /*<<< orphan*/  max_sectors; } ;
struct TYPE_2__ {scalar_t__ can_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATAPI_MAX_DRAIN ; 
 scalar_t__ ATA_DEV_ATAPI ; 
 int ATA_DFLAG_AN ; 
 int ATA_DFLAG_NCQ ; 
 int ATA_DFLAG_NO_UNLOAD ; 
 scalar_t__ ATA_DMA_PAD_SZ ; 
 scalar_t__ ATA_MAX_QUEUE ; 
 scalar_t__ ATA_SECT_SIZE ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  MSG_SIMPLE_TAG ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  SDEV_EVT_MEDIA_CHANGE ; 
 int /*<<< orphan*/  ata_dev_printk (struct ata_device*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ata_id_has_unload (int /*<<< orphan*/ ) ; 
 scalar_t__ ata_id_logical_sector_size (int /*<<< orphan*/ ) ; 
 int ata_id_queue_depth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atapi_drain_needed ; 
 int /*<<< orphan*/  blk_queue_dma_drain (struct request_queue*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_flush_queueable (struct request_queue*,int) ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_update_dma_alignment (struct request_queue*,scalar_t__) ; 
 int /*<<< orphan*/  blk_queue_update_dma_pad (struct request_queue*,scalar_t__) ; 
 void* kmalloc (int /*<<< orphan*/ ,int) ; 
 int min (scalar_t__,int) ; 
 int /*<<< orphan*/  scsi_adjust_queue_depth (struct scsi_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ata_scsi_dev_config(struct scsi_device *sdev,
			       struct ata_device *dev)
{
	struct request_queue *q = sdev->request_queue;

	if (!ata_id_has_unload(dev->id))
		dev->flags |= ATA_DFLAG_NO_UNLOAD;

	/* configure max sectors */
	blk_queue_max_hw_sectors(q, dev->max_sectors);

	if (dev->class == ATA_DEV_ATAPI) {
		void *buf;

		sdev->sector_size = ATA_SECT_SIZE;

		/* set DMA padding */
		blk_queue_update_dma_pad(q, ATA_DMA_PAD_SZ - 1);

		/* configure draining */
		buf = kmalloc(ATAPI_MAX_DRAIN, q->bounce_gfp | GFP_KERNEL);
		if (!buf) {
			ata_dev_printk(dev, KERN_ERR,
				       "drain buffer allocation failed\n");
			return -ENOMEM;
		}

		blk_queue_dma_drain(q, atapi_drain_needed, buf, ATAPI_MAX_DRAIN);
	} else {
		sdev->sector_size = ata_id_logical_sector_size(dev->id);
		sdev->manage_start_stop = 1;
	}

	/*
	 * ata_pio_sectors() expects buffer for each sector to not cross
	 * page boundary.  Enforce it by requiring buffers to be sector
	 * aligned, which works iff sector_size is not larger than
	 * PAGE_SIZE.  ATAPI devices also need the alignment as
	 * IDENTIFY_PACKET is executed as ATA_PROT_PIO.
	 */
	if (sdev->sector_size > PAGE_SIZE)
		ata_dev_printk(dev, KERN_WARNING,
			"sector_size=%u > PAGE_SIZE, PIO may malfunction\n",
			sdev->sector_size);

	blk_queue_update_dma_alignment(q, sdev->sector_size - 1);

	if (dev->flags & ATA_DFLAG_AN)
		set_bit(SDEV_EVT_MEDIA_CHANGE, sdev->supported_events);

	if (dev->flags & ATA_DFLAG_NCQ) {
		int depth;

		depth = min(sdev->host->can_queue, ata_id_queue_depth(dev->id));
		depth = min(ATA_MAX_QUEUE - 1, depth);
		scsi_adjust_queue_depth(sdev, MSG_SIMPLE_TAG, depth);
	}

	blk_queue_flush_queueable(q, false);

	dev->sdev = sdev;
	return 0;
}