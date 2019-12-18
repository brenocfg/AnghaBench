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
struct TYPE_2__ {unsigned long long sectors_per_dev; int raid_devs; } ;
struct raid_set {TYPE_1__ set; struct raid_dev* dev; struct dm_target* ti; } ;
struct raid_dev {unsigned long long start; int /*<<< orphan*/  dev; } ;
struct dm_target {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMINFO (char*,unsigned long long) ; 
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  TI_ERR (char*) ; 
 int /*<<< orphan*/  TI_ERR_RET (char*,int) ; 
 int dm_get_device (struct dm_target*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_table_get_mode (int /*<<< orphan*/ ) ; 
 int raid_dev_lookup (struct raid_set*,struct raid_dev*) ; 
 int sscanf (char*,char*,unsigned long long*) ; 

__attribute__((used)) static int dev_parms(struct raid_set *rs, char **argv, int *p)
{
	struct dm_target *ti = rs->ti;

DMINFO("rs->set.sectors_per_dev=%llu", (unsigned long long) rs->set.sectors_per_dev);
	for (*p = 0; *p < rs->set.raid_devs; (*p)++, argv += 2) {
		int r;
		unsigned long long tmp;
		struct raid_dev *dev = rs->dev + *p;

		/* Get offset and device. */
		if (sscanf(argv[1], "%llu", &tmp) != 1 ||
		    tmp > rs->set.sectors_per_dev)
			TI_ERR("Invalid RAID device offset parameter");

		dev->start = tmp;
		r = dm_get_device(ti, argv[0],
				  dm_table_get_mode(ti->table), &dev->dev);
		if (r)
			TI_ERR_RET("RAID device lookup failure", r);

		r = raid_dev_lookup(rs, dev);
		if (r != -ENODEV && r < *p) {
			(*p)++;	/* Ensure dm_put_device() on actual device. */
			TI_ERR_RET("Duplicate RAID device", -ENXIO);
		}
	}

	return 0;
}