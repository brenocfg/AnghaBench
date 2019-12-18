#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/ * vma; } ;
struct TYPE_10__ {TYPE_3__ ptr; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {int /*<<< orphan*/ * fn; } ;
struct TYPE_11__ {int /*<<< orphan*/  client; TYPE_4__ mem; TYPE_2__ notify; } ;
struct TYPE_7__ {size_t count; TYPE_6__* bdev; scalar_t__ sector; } ;
struct log_c {unsigned int region_count; int sync; size_t bitset_uint32_count; unsigned int sync_count; scalar_t__ sync_search; int /*<<< orphan*/ * disk_header; TYPE_5__ io_req; int /*<<< orphan*/ * clean_bits; int /*<<< orphan*/ * sync_bits; int /*<<< orphan*/  recovering_bits; TYPE_1__ header_location; struct dm_dev* log_dev; scalar_t__ log_dev_flush_failed; scalar_t__ log_dev_failed; int /*<<< orphan*/  region_size; scalar_t__ flush_failed; scalar_t__ touched_cleaned; scalar_t__ touched_dirtied; struct dm_target* ti; } ;
struct dm_target {int /*<<< orphan*/  len; } ;
struct dm_dirty_log {struct log_c* context; } ;
struct dm_dev {int /*<<< orphan*/  name; TYPE_6__* bdev; } ;
typedef  enum sync { ____Placeholder_sync } sync ;
struct TYPE_12__ {int /*<<< orphan*/  bd_inode; } ;

/* Variables and functions */
 int BYTE_SHIFT ; 
 int DEFAULTSYNC ; 
 int /*<<< orphan*/  DMWARN (char*,...) ; 
 int /*<<< orphan*/  DM_IO_VMA ; 
 int EINVAL ; 
 int ENOMEM ; 
 int FORCESYNC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 size_t LOG_OFFSET ; 
 int NOSYNC ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 size_t SECTOR_SHIFT ; 
 int /*<<< orphan*/  _check_region_size (struct dm_target*,int /*<<< orphan*/ ) ; 
 int bdev_logical_block_size (TYPE_6__*) ; 
 int /*<<< orphan*/  dm_io_client_create () ; 
 int /*<<< orphan*/  dm_io_client_destroy (int /*<<< orphan*/ ) ; 
 size_t dm_round_up (size_t,int) ; 
 unsigned int dm_sector_div_up (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t i_size_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct log_c*) ; 
 struct log_c* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,size_t) ; 
 int sscanf (char*,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 void* vmalloc (size_t) ; 
 int /*<<< orphan*/  vzalloc (size_t) ; 

__attribute__((used)) static int create_log_context(struct dm_dirty_log *log, struct dm_target *ti,
			      unsigned int argc, char **argv,
			      struct dm_dev *dev)
{
	enum sync sync = DEFAULTSYNC;

	struct log_c *lc;
	uint32_t region_size;
	unsigned int region_count;
	size_t bitset_size, buf_size;
	int r;
	char dummy;

	if (argc < 1 || argc > 2) {
		DMWARN("wrong number of arguments to dirty region log");
		return -EINVAL;
	}

	if (argc > 1) {
		if (!strcmp(argv[1], "sync"))
			sync = FORCESYNC;
		else if (!strcmp(argv[1], "nosync"))
			sync = NOSYNC;
		else {
			DMWARN("unrecognised sync argument to "
			       "dirty region log: %s", argv[1]);
			return -EINVAL;
		}
	}

	if (sscanf(argv[0], "%u%c", &region_size, &dummy) != 1 ||
	    !_check_region_size(ti, region_size)) {
		DMWARN("invalid region size %s", argv[0]);
		return -EINVAL;
	}

	region_count = dm_sector_div_up(ti->len, region_size);

	lc = kmalloc(sizeof(*lc), GFP_KERNEL);
	if (!lc) {
		DMWARN("couldn't allocate core log");
		return -ENOMEM;
	}

	lc->ti = ti;
	lc->touched_dirtied = 0;
	lc->touched_cleaned = 0;
	lc->flush_failed = 0;
	lc->region_size = region_size;
	lc->region_count = region_count;
	lc->sync = sync;

	/*
	 * Work out how many "unsigned long"s we need to hold the bitset.
	 */
	bitset_size = dm_round_up(region_count,
				  sizeof(*lc->clean_bits) << BYTE_SHIFT);
	bitset_size >>= BYTE_SHIFT;

	lc->bitset_uint32_count = bitset_size / sizeof(*lc->clean_bits);

	/*
	 * Disk log?
	 */
	if (!dev) {
		lc->clean_bits = vmalloc(bitset_size);
		if (!lc->clean_bits) {
			DMWARN("couldn't allocate clean bitset");
			kfree(lc);
			return -ENOMEM;
		}
		lc->disk_header = NULL;
	} else {
		lc->log_dev = dev;
		lc->log_dev_failed = 0;
		lc->log_dev_flush_failed = 0;
		lc->header_location.bdev = lc->log_dev->bdev;
		lc->header_location.sector = 0;

		/*
		 * Buffer holds both header and bitset.
		 */
		buf_size =
		    dm_round_up((LOG_OFFSET << SECTOR_SHIFT) + bitset_size,
				bdev_logical_block_size(lc->header_location.
							    bdev));

		if (buf_size > i_size_read(dev->bdev->bd_inode)) {
			DMWARN("log device %s too small: need %llu bytes",
				dev->name, (unsigned long long)buf_size);
			kfree(lc);
			return -EINVAL;
		}

		lc->header_location.count = buf_size >> SECTOR_SHIFT;

		lc->io_req.mem.type = DM_IO_VMA;
		lc->io_req.notify.fn = NULL;
		lc->io_req.client = dm_io_client_create();
		if (IS_ERR(lc->io_req.client)) {
			r = PTR_ERR(lc->io_req.client);
			DMWARN("couldn't allocate disk io client");
			kfree(lc);
			return r;
		}

		lc->disk_header = vmalloc(buf_size);
		if (!lc->disk_header) {
			DMWARN("couldn't allocate disk log buffer");
			dm_io_client_destroy(lc->io_req.client);
			kfree(lc);
			return -ENOMEM;
		}

		lc->io_req.mem.ptr.vma = lc->disk_header;
		lc->clean_bits = (void *)lc->disk_header +
				 (LOG_OFFSET << SECTOR_SHIFT);
	}

	memset(lc->clean_bits, -1, bitset_size);

	lc->sync_bits = vmalloc(bitset_size);
	if (!lc->sync_bits) {
		DMWARN("couldn't allocate sync bitset");
		if (!dev)
			vfree(lc->clean_bits);
		else
			dm_io_client_destroy(lc->io_req.client);
		vfree(lc->disk_header);
		kfree(lc);
		return -ENOMEM;
	}
	memset(lc->sync_bits, (sync == NOSYNC) ? -1 : 0, bitset_size);
	lc->sync_count = (sync == NOSYNC) ? region_count : 0;

	lc->recovering_bits = vzalloc(bitset_size);
	if (!lc->recovering_bits) {
		DMWARN("couldn't allocate sync bitset");
		vfree(lc->sync_bits);
		if (!dev)
			vfree(lc->clean_bits);
		else
			dm_io_client_destroy(lc->io_req.client);
		vfree(lc->disk_header);
		kfree(lc);
		return -ENOMEM;
	}
	lc->sync_search = 0;
	log->context = lc;

	return 0;
}