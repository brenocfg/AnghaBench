#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int chunk_size_parm; int io_size_parm; unsigned int raid_devs; unsigned int pi; unsigned int dev_to_init; unsigned long long raid_parms; TYPE_3__* raid_type; } ;
struct TYPE_12__ {int io_size_parm; int bandwidth_parm; int recovery_stripes; int /*<<< orphan*/  recovery; struct dm_dirty_log* dl; scalar_t__ nr_regions; } ;
struct TYPE_9__ {int stripes_parm; } ;
struct raid_set {TYPE_8__* dev; TYPE_5__ set; TYPE_4__ recover; TYPE_1__ sc; } ;
struct dm_target {struct raid_set* private; } ;
struct dm_dirty_log {TYPE_2__* type; } ;
typedef  int status_type_t ;
struct TYPE_16__ {scalar_t__ start; TYPE_7__* dev; } ;
struct TYPE_15__ {TYPE_6__* bdev; } ;
struct TYPE_14__ {int /*<<< orphan*/  bd_dev; } ;
struct TYPE_11__ {unsigned long long name; } ;
struct TYPE_10__ {unsigned int (* status ) (struct dm_dirty_log*,int,char*,unsigned int) ;scalar_t__ (* get_sync_count ) (struct dm_dirty_log*) ;} ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  DMEMIT (char*,...) ; 
 int /*<<< orphan*/  DevFailed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSDevelStats (struct raid_set*) ; 
#define  STATUSTYPE_INFO 129 
#define  STATUSTYPE_TABLE 128 
 unsigned long long format_dev_t (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raid_devel_stats (struct dm_target*,char*,unsigned int*,unsigned int) ; 
 scalar_t__ stub1 (struct dm_dirty_log*) ; 
 unsigned int stub2 (struct dm_dirty_log*,int,char*,unsigned int) ; 
 unsigned int stub3 (struct dm_dirty_log*,int,char*,unsigned int) ; 

__attribute__((used)) static int raid_status(struct dm_target *ti, status_type_t type,
		       char *result, unsigned maxlen)
{
	unsigned p, sz = 0;
	char buf[BDEVNAME_SIZE];
	struct raid_set *rs = ti->private;
	struct dm_dirty_log *dl = rs->recover.dl;
	int raid_parms[] = {
		rs->set.chunk_size_parm,
		rs->sc.stripes_parm,
		rs->set.io_size_parm,
		rs->recover.io_size_parm,
		rs->recover.bandwidth_parm,
		-2,
		rs->recover.recovery_stripes,
	};

	switch (type) {
	case STATUSTYPE_INFO:
		/* REMOVEME: statistics. */
		if (RSDevelStats(rs))
			raid_devel_stats(ti, result, &sz, maxlen);

		DMEMIT("%u ", rs->set.raid_devs);

		for (p = 0; p < rs->set.raid_devs; p++)
			DMEMIT("%s ",
			       format_dev_t(buf, rs->dev[p].dev->bdev->bd_dev));

		DMEMIT("2 ");
		for (p = 0; p < rs->set.raid_devs; p++) {
			DMEMIT("%c", !DevFailed(rs->dev + p) ? 'A' : 'D');

			if (p == rs->set.pi)
				DMEMIT("p");

			if (p == rs->set.dev_to_init)
				DMEMIT("i");
		}

		DMEMIT(" %llu/%llu ",
		      (unsigned long long) dl->type->get_sync_count(dl),
		      (unsigned long long) rs->recover.nr_regions);

		sz += dl->type->status(dl, type, result+sz, maxlen-sz);
		break;
	case STATUSTYPE_TABLE:
		sz = rs->recover.dl->type->status(rs->recover.dl, type,
						  result, maxlen);
		DMEMIT("%s %u ", rs->set.raid_type->name, rs->set.raid_parms);

		for (p = 0; p < rs->set.raid_parms; p++) {
			if (raid_parms[p] > -2)
				DMEMIT("%d ", raid_parms[p]);
			else
				DMEMIT("%s ", rs->recover.recovery ?
					      "sync" : "nosync");
		}

		DMEMIT("%u %d ", rs->set.raid_devs, rs->set.dev_to_init);

		for (p = 0; p < rs->set.raid_devs; p++)
			DMEMIT("%s %llu ",
			       format_dev_t(buf, rs->dev[p].dev->bdev->bd_dev),
			       (unsigned long long) rs->dev[p].start);
	}

	return 0;
}