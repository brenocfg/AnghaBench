#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct raid_type {int dummy; } ;
struct TYPE_5__ {scalar_t__ array_sectors; int /*<<< orphan*/  reconfig_mutex; scalar_t__ in_sync; int /*<<< orphan*/  event_work; int /*<<< orphan*/  sync_super; } ;
struct TYPE_6__ {int /*<<< orphan*/  unplug_fn; int /*<<< orphan*/  congested_fn; } ;
struct raid_set {TYPE_1__ md; TYPE_4__ callbacks; } ;
struct dm_target {char* error; int num_flush_requests; scalar_t__ len; int /*<<< orphan*/  table; struct raid_set* private; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long INT_MAX ; 
 scalar_t__ IS_ERR (struct raid_set*) ; 
 int PTR_ERR (struct raid_set*) ; 
 int analyse_superblocks (struct dm_target*,struct raid_set*) ; 
 struct raid_set* context_alloc (struct dm_target*,struct raid_type*,unsigned int) ; 
 int /*<<< orphan*/  context_free (struct raid_set*) ; 
 int dev_parms (struct raid_set*,char**) ; 
 int /*<<< orphan*/  dm_table_add_target_callbacks (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  do_table_event ; 
 struct raid_type* get_raid_type (char*) ; 
 scalar_t__ kstrtoul (char*,int,unsigned long*) ; 
 int md_run (TYPE_1__*) ; 
 int /*<<< orphan*/  md_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  mddev_suspend (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int parse_raid_params (struct raid_set*,char**,unsigned int) ; 
 int /*<<< orphan*/  raid_is_congested ; 
 int /*<<< orphan*/  raid_unplug ; 
 int /*<<< orphan*/  super_sync ; 

__attribute__((used)) static int raid_ctr(struct dm_target *ti, unsigned argc, char **argv)
{
	int ret;
	struct raid_type *rt;
	unsigned long num_raid_params, num_raid_devs;
	struct raid_set *rs = NULL;

	/* Must have at least <raid_type> <#raid_params> */
	if (argc < 2) {
		ti->error = "Too few arguments";
		return -EINVAL;
	}

	/* raid type */
	rt = get_raid_type(argv[0]);
	if (!rt) {
		ti->error = "Unrecognised raid_type";
		return -EINVAL;
	}
	argc--;
	argv++;

	/* number of RAID parameters */
	if (kstrtoul(argv[0], 10, &num_raid_params) < 0) {
		ti->error = "Cannot understand number of RAID parameters";
		return -EINVAL;
	}
	argc--;
	argv++;

	/* Skip over RAID params for now and find out # of devices */
	if (num_raid_params + 1 > argc) {
		ti->error = "Arguments do not agree with counts given";
		return -EINVAL;
	}

	if ((kstrtoul(argv[num_raid_params], 10, &num_raid_devs) < 0) ||
	    (num_raid_devs >= INT_MAX)) {
		ti->error = "Cannot understand number of raid devices";
		return -EINVAL;
	}

	rs = context_alloc(ti, rt, (unsigned)num_raid_devs);
	if (IS_ERR(rs))
		return PTR_ERR(rs);

	ret = parse_raid_params(rs, argv, (unsigned)num_raid_params);
	if (ret)
		goto bad;

	ret = -EINVAL;

	argc -= num_raid_params + 1; /* +1: we already have num_raid_devs */
	argv += num_raid_params + 1;

	if (argc != (num_raid_devs * 2)) {
		ti->error = "Supplied RAID devices does not match the count given";
		goto bad;
	}

	ret = dev_parms(rs, argv);
	if (ret)
		goto bad;

	rs->md.sync_super = super_sync;
	ret = analyse_superblocks(ti, rs);
	if (ret)
		goto bad;

	INIT_WORK(&rs->md.event_work, do_table_event);
	ti->private = rs;
	ti->num_flush_requests = 1;

	mutex_lock(&rs->md.reconfig_mutex);
	ret = md_run(&rs->md);
	rs->md.in_sync = 0; /* Assume already marked dirty */
	mutex_unlock(&rs->md.reconfig_mutex);

	if (ret) {
		ti->error = "Fail to run raid array";
		goto bad;
	}

	if (ti->len != rs->md.array_sectors) {
		ti->error = "Array size does not match requested target length";
		ret = -EINVAL;
		goto size_mismatch;
	}
	rs->callbacks.congested_fn = raid_is_congested;
	rs->callbacks.unplug_fn = raid_unplug;
	dm_table_add_target_callbacks(ti->table, &rs->callbacks);

	mddev_suspend(&rs->md);
	return 0;

size_mismatch:
	md_stop(&rs->md);
bad:
	context_free(rs);

	return ret;
}