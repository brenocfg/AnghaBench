#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct super_block {scalar_t__ s_bdev; } ;
struct TYPE_5__ {char* name; int ra_pages; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  unplug_io_fn; } ;
struct fuse_conn {int bdi_initialized; TYPE_1__ bdi; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDI_CAP_NO_ACCT_WB ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int PAGE_CACHE_SIZE ; 
 int VM_MAX_READAHEAD ; 
 int bdi_init (TYPE_1__*) ; 
 int bdi_register (TYPE_1__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bdi_register_dev (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdi_set_max_ratio (TYPE_1__*,int) ; 
 int /*<<< orphan*/  default_unplug_io_fn ; 

__attribute__((used)) static int fuse_bdi_init(struct fuse_conn *fc, struct super_block *sb)
{
	int err;

	fc->bdi.name = "fuse";
	fc->bdi.ra_pages = (VM_MAX_READAHEAD * 1024) / PAGE_CACHE_SIZE;
	fc->bdi.unplug_io_fn = default_unplug_io_fn;
	/* fuse does it's own writeback accounting */
	fc->bdi.capabilities = BDI_CAP_NO_ACCT_WB;

	err = bdi_init(&fc->bdi);
	if (err)
		return err;

	fc->bdi_initialized = 1;

	if (sb->s_bdev) {
		err =  bdi_register(&fc->bdi, NULL, "%u:%u-fuseblk",
				    MAJOR(fc->dev), MINOR(fc->dev));
	} else {
		err = bdi_register_dev(&fc->bdi, fc->dev);
	}

	if (err)
		return err;

	/*
	 * For a single fuse filesystem use max 1% of dirty +
	 * writeback threshold.
	 *
	 * This gives about 1M of write buffer for memory maps on a
	 * machine with 1G and 10% dirty_ratio, which should be more
	 * than enough.
	 *
	 * Privileged users can raise it by writing to
	 *
	 *    /sys/class/bdi/<bdi>/max_ratio
	 */
	bdi_set_max_ratio(&fc->bdi, 1);

	return 0;
}