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
struct scsi_disk {int /*<<< orphan*/  capacity; TYPE_1__* disk; scalar_t__ DPOFUA; scalar_t__ WCE; scalar_t__ first_scan; scalar_t__ media_present; struct scsi_device* device; } ;
struct scsi_device {int dummy; } ;
struct gendisk {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 unsigned int REQ_FLUSH ; 
 unsigned int REQ_FUA ; 
 int /*<<< orphan*/  SCSI_LOG_HLQUEUE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SD_BUF_SIZE ; 
 int /*<<< orphan*/  blk_queue_flush (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_device_online (struct scsi_device*) ; 
 struct scsi_disk* scsi_disk (struct gendisk*) ; 
 int /*<<< orphan*/  sd_printk (int /*<<< orphan*/ ,struct scsi_disk*,char*) ; 
 int /*<<< orphan*/  sd_read_app_tag_own (struct scsi_disk*,unsigned char*) ; 
 int /*<<< orphan*/  sd_read_block_characteristics (struct scsi_disk*) ; 
 int /*<<< orphan*/  sd_read_block_limits (struct scsi_disk*) ; 
 int /*<<< orphan*/  sd_read_block_provisioning (struct scsi_disk*) ; 
 int /*<<< orphan*/  sd_read_cache_type (struct scsi_disk*,unsigned char*) ; 
 int /*<<< orphan*/  sd_read_capacity (struct scsi_disk*,unsigned char*) ; 
 int /*<<< orphan*/  sd_read_write_protect_flag (struct scsi_disk*,unsigned char*) ; 
 int /*<<< orphan*/  sd_spinup_disk (struct scsi_disk*) ; 
 scalar_t__ sd_try_extended_inquiry (struct scsi_device*) ; 
 int /*<<< orphan*/  set_capacity (struct gendisk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_revalidate_disk(struct gendisk *disk)
{
	struct scsi_disk *sdkp = scsi_disk(disk);
	struct scsi_device *sdp = sdkp->device;
	unsigned char *buffer;
	unsigned flush = 0;

	SCSI_LOG_HLQUEUE(3, sd_printk(KERN_INFO, sdkp,
				      "sd_revalidate_disk\n"));

	/*
	 * If the device is offline, don't try and read capacity or any
	 * of the other niceties.
	 */
	if (!scsi_device_online(sdp))
		goto out;

	buffer = kmalloc(SD_BUF_SIZE, GFP_KERNEL);
	if (!buffer) {
		sd_printk(KERN_WARNING, sdkp, "sd_revalidate_disk: Memory "
			  "allocation failure.\n");
		goto out;
	}

	sd_spinup_disk(sdkp);

	/*
	 * Without media there is no reason to ask; moreover, some devices
	 * react badly if we do.
	 */
	if (sdkp->media_present) {
		sd_read_capacity(sdkp, buffer);

		if (sd_try_extended_inquiry(sdp)) {
			sd_read_block_provisioning(sdkp);
			sd_read_block_limits(sdkp);
			sd_read_block_characteristics(sdkp);
		}

		sd_read_write_protect_flag(sdkp, buffer);
		sd_read_cache_type(sdkp, buffer);
		sd_read_app_tag_own(sdkp, buffer);
	}

	sdkp->first_scan = 0;

	/*
	 * We now have all cache related info, determine how we deal
	 * with flush requests.
	 */
	if (sdkp->WCE) {
		flush |= REQ_FLUSH;
		if (sdkp->DPOFUA)
			flush |= REQ_FUA;
	}

	blk_queue_flush(sdkp->disk->queue, flush);

	set_capacity(disk, sdkp->capacity);
	kfree(buffer);

 out:
	return 0;
}