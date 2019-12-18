#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u64 ;
struct scsi_disk {int capacity; int physical_block_size; struct scsi_device* device; scalar_t__ first_scan; } ;
struct scsi_device {int sector_size; int /*<<< orphan*/  request_queue; scalar_t__ guess_capacity; scalar_t__ fix_capacity; } ;
typedef  int sector_t ;
typedef  int /*<<< orphan*/  cap_str_2 ;
typedef  int /*<<< orphan*/  cap_str_10 ;

/* Variables and functions */
 int ENODEV ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 int /*<<< orphan*/  STRING_UNITS_10 ; 
 int /*<<< orphan*/  STRING_UNITS_2 ; 
 int /*<<< orphan*/  blk_queue_logical_block_size (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  blk_queue_physical_block_size (int /*<<< orphan*/ ,int) ; 
 int ilog2 (int) ; 
 int read_capacity_10 (struct scsi_disk*,struct scsi_device*,unsigned char*) ; 
 int read_capacity_16 (struct scsi_disk*,struct scsi_device*,unsigned char*) ; 
 int /*<<< orphan*/  sd_printk (int /*<<< orphan*/ ,struct scsi_disk*,char*,...) ; 
 scalar_t__ sd_try_rc16_first (struct scsi_device*) ; 
 int /*<<< orphan*/  string_get_size (int,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
sd_read_capacity(struct scsi_disk *sdkp, unsigned char *buffer)
{
	int sector_size;
	struct scsi_device *sdp = sdkp->device;
	sector_t old_capacity = sdkp->capacity;

	if (sd_try_rc16_first(sdp)) {
		sector_size = read_capacity_16(sdkp, sdp, buffer);
		if (sector_size == -EOVERFLOW)
			goto got_data;
		if (sector_size == -ENODEV)
			return;
		if (sector_size < 0)
			sector_size = read_capacity_10(sdkp, sdp, buffer);
		if (sector_size < 0)
			return;
	} else {
		sector_size = read_capacity_10(sdkp, sdp, buffer);
		if (sector_size == -EOVERFLOW)
			goto got_data;
		if (sector_size < 0)
			return;
		if ((sizeof(sdkp->capacity) > 4) &&
		    (sdkp->capacity > 0xffffffffULL)) {
			int old_sector_size = sector_size;
			sd_printk(KERN_NOTICE, sdkp, "Very big device. "
					"Trying to use READ CAPACITY(16).\n");
			sector_size = read_capacity_16(sdkp, sdp, buffer);
			if (sector_size < 0) {
				sd_printk(KERN_NOTICE, sdkp,
					"Using 0xffffffff as device size\n");
				sdkp->capacity = 1 + (sector_t) 0xffffffff;
				sector_size = old_sector_size;
				goto got_data;
			}
		}
	}

	/* Some devices are known to return the total number of blocks,
	 * not the highest block number.  Some devices have versions
	 * which do this and others which do not.  Some devices we might
	 * suspect of doing this but we don't know for certain.
	 *
	 * If we know the reported capacity is wrong, decrement it.  If
	 * we can only guess, then assume the number of blocks is even
	 * (usually true but not always) and err on the side of lowering
	 * the capacity.
	 */
	if (sdp->fix_capacity ||
	    (sdp->guess_capacity && (sdkp->capacity & 0x01))) {
		sd_printk(KERN_INFO, sdkp, "Adjusting the sector count "
				"from its reported value: %llu\n",
				(unsigned long long) sdkp->capacity);
		--sdkp->capacity;
	}

got_data:
	if (sector_size == 0) {
		sector_size = 512;
		sd_printk(KERN_NOTICE, sdkp, "Sector size 0 reported, "
			  "assuming 512.\n");
	}

	if (sector_size != 512 &&
	    sector_size != 1024 &&
	    sector_size != 2048 &&
	    sector_size != 4096 &&
	    sector_size != 256) {
		sd_printk(KERN_NOTICE, sdkp, "Unsupported sector size %d.\n",
			  sector_size);
		/*
		 * The user might want to re-format the drive with
		 * a supported sectorsize.  Once this happens, it
		 * would be relatively trivial to set the thing up.
		 * For this reason, we leave the thing in the table.
		 */
		sdkp->capacity = 0;
		/*
		 * set a bogus sector size so the normal read/write
		 * logic in the block layer will eventually refuse any
		 * request on this device without tripping over power
		 * of two sector size assumptions
		 */
		sector_size = 512;
	}
	blk_queue_logical_block_size(sdp->request_queue, sector_size);

	{
		char cap_str_2[10], cap_str_10[10];
		u64 sz = (u64)sdkp->capacity << ilog2(sector_size);

		string_get_size(sz, STRING_UNITS_2, cap_str_2,
				sizeof(cap_str_2));
		string_get_size(sz, STRING_UNITS_10, cap_str_10,
				sizeof(cap_str_10));

		if (sdkp->first_scan || old_capacity != sdkp->capacity) {
			sd_printk(KERN_NOTICE, sdkp,
				  "%llu %d-byte logical blocks: (%s/%s)\n",
				  (unsigned long long)sdkp->capacity,
				  sector_size, cap_str_10, cap_str_2);

			if (sdkp->physical_block_size != sector_size)
				sd_printk(KERN_NOTICE, sdkp,
					  "%u-byte physical blocks\n",
					  sdkp->physical_block_size);
		}
	}

	/* Rescale capacity to 512-byte units */
	if (sector_size == 4096)
		sdkp->capacity <<= 3;
	else if (sector_size == 2048)
		sdkp->capacity <<= 2;
	else if (sector_size == 1024)
		sdkp->capacity <<= 1;
	else if (sector_size == 256)
		sdkp->capacity >>= 1;

	blk_queue_physical_block_size(sdp->request_queue,
				      sdkp->physical_block_size);
	sdkp->device->sector_size = sector_size;
}