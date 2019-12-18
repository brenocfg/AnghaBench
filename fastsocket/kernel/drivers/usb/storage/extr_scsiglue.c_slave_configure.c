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
struct us_data {int fflags; scalar_t__ subclass; scalar_t__ protocol; int use_last_sector_hacks; scalar_t__ max_lun; TYPE_4__* pusb_dev; } ;
struct scsi_device {scalar_t__ type; int use_10_for_ms; int use_192_bytes_for_3f; int skip_ms_page_3f; int skip_ms_page_8; int fix_capacity; int guess_capacity; scalar_t__ scsi_level; int retry_hwerror; int allow_restart; int last_sector_bug; scalar_t__ lockable; TYPE_5__* sdev_target; int /*<<< orphan*/  request_queue; int /*<<< orphan*/  host; } ;
struct TYPE_10__ {scalar_t__ scsi_level; } ;
struct TYPE_8__ {int /*<<< orphan*/  idVendor; } ;
struct TYPE_9__ {TYPE_3__ descriptor; TYPE_2__* bus; } ;
struct TYPE_7__ {TYPE_1__* controller; } ;
struct TYPE_6__ {int /*<<< orphan*/  dma_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_BOUNCE_HIGH ; 
 int PAGE_CACHE_SIZE ; 
 scalar_t__ SCSI_2 ; 
 scalar_t__ SCSI_SPC_2 ; 
 scalar_t__ SCSI_UNKNOWN ; 
 scalar_t__ TYPE_DISK ; 
 scalar_t__ TYPE_TAPE ; 
 int US_FL_CAPACITY_HEURISTICS ; 
 int US_FL_CAPACITY_OK ; 
 int US_FL_FIX_CAPACITY ; 
 int US_FL_MAX_SECTORS_64 ; 
 int US_FL_MAX_SECTORS_MIN ; 
 int US_FL_NOT_LOCKABLE ; 
 int US_FL_NO_WP_DETECT ; 
 int US_FL_SANE_SENSE ; 
 int US_FL_SCM_MULT_TARG ; 
 scalar_t__ US_PR_BULK ; 
 scalar_t__ US_PR_CB ; 
 scalar_t__ US_PR_CBI ; 
 scalar_t__ US_SC_CYP_ATACB ; 
 scalar_t__ US_SC_SCSI ; 
#define  VENDOR_ID_MOTOROLA 131 
#define  VENDOR_ID_NIKON 130 
#define  VENDOR_ID_NOKIA 129 
#define  VENDOR_ID_PENTAX 128 
 int /*<<< orphan*/  blk_queue_bounce_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (int /*<<< orphan*/ ,int) ; 
 struct us_data* host_to_us (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int queue_max_hw_sectors (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int slave_configure(struct scsi_device *sdev)
{
	struct us_data *us = host_to_us(sdev->host);

	/* Many devices have trouble transfering more than 32KB at a time,
	 * while others have trouble with more than 64K. At this time we
	 * are limiting both to 32K (64 sectores).
	 */
	if (us->fflags & (US_FL_MAX_SECTORS_64 | US_FL_MAX_SECTORS_MIN)) {
		unsigned int max_sectors = 64;

		if (us->fflags & US_FL_MAX_SECTORS_MIN)
			max_sectors = PAGE_CACHE_SIZE >> 9;
		if (queue_max_hw_sectors(sdev->request_queue) > max_sectors)
			blk_queue_max_hw_sectors(sdev->request_queue,
					      max_sectors);
	} else if (sdev->type == TYPE_TAPE) {
		/* Tapes need much higher max_sector limits, so just
		 * raise it to the maximum possible (4 GB / 512) and
		 * let the queue segment size sort out the real limit.
		 */
		blk_queue_max_hw_sectors(sdev->request_queue, 0x7FFFFF);
	}

	/* Some USB host controllers can't do DMA; they have to use PIO.
	 * They indicate this by setting their dma_mask to NULL.  For
	 * such controllers we need to make sure the block layer sets
	 * up bounce buffers in addressable memory.
	 */
	if (!us->pusb_dev->bus->controller->dma_mask)
		blk_queue_bounce_limit(sdev->request_queue, BLK_BOUNCE_HIGH);

	/* We can't put these settings in slave_alloc() because that gets
	 * called before the device type is known.  Consequently these
	 * settings can't be overridden via the scsi devinfo mechanism. */
	if (sdev->type == TYPE_DISK) {

		/* Some vendors seem to put the READ CAPACITY bug into
		 * all their devices -- primarily makers of cell phones
		 * and digital cameras.  Since these devices always use
		 * flash media and can be expected to have an even number
		 * of sectors, we will always enable the CAPACITY_HEURISTICS
		 * flag unless told otherwise. */
		switch (le16_to_cpu(us->pusb_dev->descriptor.idVendor)) {
		case VENDOR_ID_NOKIA:
		case VENDOR_ID_NIKON:
		case VENDOR_ID_PENTAX:
		case VENDOR_ID_MOTOROLA:
			if (!(us->fflags & (US_FL_FIX_CAPACITY |
					US_FL_CAPACITY_OK)))
				us->fflags |= US_FL_CAPACITY_HEURISTICS;
			break;
		}

		/* Disk-type devices use MODE SENSE(6) if the protocol
		 * (SubClass) is Transparent SCSI, otherwise they use
		 * MODE SENSE(10). */
		if (us->subclass != US_SC_SCSI && us->subclass != US_SC_CYP_ATACB)
			sdev->use_10_for_ms = 1;

		/* Many disks only accept MODE SENSE transfer lengths of
		 * 192 bytes (that's what Windows uses). */
		sdev->use_192_bytes_for_3f = 1;

		/* Some devices don't like MODE SENSE with page=0x3f,
		 * which is the command used for checking if a device
		 * is write-protected.  Now that we tell the sd driver
		 * to do a 192-byte transfer with this command the
		 * majority of devices work fine, but a few still can't
		 * handle it.  The sd driver will simply assume those
		 * devices are write-enabled. */
		if (us->fflags & US_FL_NO_WP_DETECT)
			sdev->skip_ms_page_3f = 1;

		/* A number of devices have problems with MODE SENSE for
		 * page x08, so we will skip it. */
		sdev->skip_ms_page_8 = 1;

		/* Some disks return the total number of blocks in response
		 * to READ CAPACITY rather than the highest block number.
		 * If this device makes that mistake, tell the sd driver. */
		if (us->fflags & US_FL_FIX_CAPACITY)
			sdev->fix_capacity = 1;

		/* A few disks have two indistinguishable version, one of
		 * which reports the correct capacity and the other does not.
		 * The sd driver has to guess which is the case. */
		if (us->fflags & US_FL_CAPACITY_HEURISTICS)
			sdev->guess_capacity = 1;

		/* assume SPC3 or latter devices support sense size > 18 */
		if (sdev->scsi_level > SCSI_SPC_2)
			us->fflags |= US_FL_SANE_SENSE;

		/* Some devices report a SCSI revision level above 2 but are
		 * unable to handle the REPORT LUNS command (for which
		 * support is mandatory at level 3).  Since we already have
		 * a Get-Max-LUN request, we won't lose much by setting the
		 * revision level down to 2.  The only devices that would be
		 * affected are those with sparse LUNs. */
		if (sdev->scsi_level > SCSI_2)
			sdev->sdev_target->scsi_level =
					sdev->scsi_level = SCSI_2;

		/* USB-IDE bridges tend to report SK = 0x04 (Non-recoverable
		 * Hardware Error) when any low-level error occurs,
		 * recoverable or not.  Setting this flag tells the SCSI
		 * midlayer to retry such commands, which frequently will
		 * succeed and fix the error.  The worst this can lead to
		 * is an occasional series of retries that will all fail. */
		sdev->retry_hwerror = 1;

		/* USB disks should allow restart.  Some drives spin down
		 * automatically, requiring a START-STOP UNIT command. */
		sdev->allow_restart = 1;

		/* Some USB cardreaders have trouble reading an sdcard's last
		 * sector in a larger then 1 sector read, since the performance
		 * impact is negible we set this flag for all USB disks */
		sdev->last_sector_bug = 1;

		/* Enable last-sector hacks for single-target devices using
		 * the Bulk-only transport, unless we already know the
		 * capacity will be decremented or is correct. */
		if (!(us->fflags & (US_FL_FIX_CAPACITY | US_FL_CAPACITY_OK |
					US_FL_SCM_MULT_TARG)) &&
				us->protocol == US_PR_BULK)
			us->use_last_sector_hacks = 1;
	} else {

		/* Non-disk-type devices don't need to blacklist any pages
		 * or to force 192-byte transfer lengths for MODE SENSE.
		 * But they do need to use MODE SENSE(10). */
		sdev->use_10_for_ms = 1;
	}

	/* The CB and CBI transports have no way to pass LUN values
	 * other than the bits in the second byte of a CDB.  But those
	 * bits don't get set to the LUN value if the device reports
	 * scsi_level == 0 (UNKNOWN).  Hence such devices must necessarily
	 * be single-LUN.
	 */
	if ((us->protocol == US_PR_CB || us->protocol == US_PR_CBI) &&
			sdev->scsi_level == SCSI_UNKNOWN)
		us->max_lun = 0;

	/* Some devices choke when they receive a PREVENT-ALLOW MEDIUM
	 * REMOVAL command, so suppress those commands. */
	if (us->fflags & US_FL_NOT_LOCKABLE)
		sdev->lockable = 0;

	/* this is to satisfy the compiler, tho I don't think the 
	 * return code is ever checked anywhere. */
	return 0;
}