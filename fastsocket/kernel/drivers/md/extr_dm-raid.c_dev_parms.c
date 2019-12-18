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
struct TYPE_8__ {int raid_disks; int persistent; int major_version; int /*<<< orphan*/  recovery_cp; scalar_t__ external; int /*<<< orphan*/  disks; } ;
struct raid_set {TYPE_4__* ti; TYPE_3__ md; TYPE_2__* dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_9__ {char* error; int /*<<< orphan*/  table; } ;
struct TYPE_6__ {int raid_disk; int /*<<< orphan*/  flags; int /*<<< orphan*/  same_set; int /*<<< orphan*/  bdev; int /*<<< orphan*/  meta_bdev; int /*<<< orphan*/  recovery_offset; int /*<<< orphan*/  sb_page; TYPE_3__* mddev; scalar_t__ data_offset; } ;
struct TYPE_7__ {TYPE_1__ rdev; TYPE_5__* data_dev; TYPE_5__* meta_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  In_sync ; 
 int /*<<< orphan*/  alloc_page (int /*<<< orphan*/ ) ; 
 int dm_get_device (TYPE_4__*,char*,int /*<<< orphan*/ ,TYPE_5__**) ; 
 int /*<<< orphan*/  dm_table_get_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dev_parms(struct raid_set *rs, char **argv)
{
	int i;
	int rebuild = 0;
	int metadata_available = 0;
	int ret = 0;

	for (i = 0; i < rs->md.raid_disks; i++, argv += 2) {
		rs->dev[i].rdev.raid_disk = i;

		rs->dev[i].meta_dev = NULL;
		rs->dev[i].data_dev = NULL;

		/*
		 * There are no offsets, since there is a separate device
		 * for data and metadata.
		 */
		rs->dev[i].rdev.data_offset = 0;
		rs->dev[i].rdev.mddev = &rs->md;

		if (strcmp(argv[0], "-")) {
			ret = dm_get_device(rs->ti, argv[0],
					    dm_table_get_mode(rs->ti->table),
					    &rs->dev[i].meta_dev);
			rs->ti->error = "RAID metadata device lookup failure";
			if (ret)
				return ret;

			rs->dev[i].rdev.sb_page = alloc_page(GFP_KERNEL);
			if (!rs->dev[i].rdev.sb_page)
				return -ENOMEM;
		}

		if (!strcmp(argv[1], "-")) {
			if (!test_bit(In_sync, &rs->dev[i].rdev.flags) &&
			    (!rs->dev[i].rdev.recovery_offset)) {
				rs->ti->error = "Drive designated for rebuild not specified";
				return -EINVAL;
			}

			rs->ti->error = "No data device supplied with metadata device";
			if (rs->dev[i].meta_dev)
				return -EINVAL;

			continue;
		}

		ret = dm_get_device(rs->ti, argv[1],
				    dm_table_get_mode(rs->ti->table),
				    &rs->dev[i].data_dev);
		if (ret) {
			rs->ti->error = "RAID device lookup failure";
			return ret;
		}

		if (rs->dev[i].meta_dev) {
			metadata_available = 1;
			rs->dev[i].rdev.meta_bdev = rs->dev[i].meta_dev->bdev;
		}
		rs->dev[i].rdev.bdev = rs->dev[i].data_dev->bdev;
		list_add(&rs->dev[i].rdev.same_set, &rs->md.disks);
		if (!test_bit(In_sync, &rs->dev[i].rdev.flags))
			rebuild++;
	}

	if (metadata_available) {
		rs->md.external = 0;
		rs->md.persistent = 1;
		rs->md.major_version = 2;
	} else if (rebuild && !rs->md.recovery_cp) {
		/*
		 * Without metadata, we will not be able to tell if the array
		 * is in-sync or not - we must assume it is not.  Therefore,
		 * it is impossible to rebuild a drive.
		 *
		 * Even if there is metadata, the on-disk information may
		 * indicate that the array is not in-sync and it will then
		 * fail at that time.
		 *
		 * User could specify 'nosync' option if desperate.
		 */
		DMERR("Unable to rebuild drive while array is not in-sync");
		rs->ti->error = "RAID device lookup failure";
		return -EINVAL;
	}

	return 0;
}