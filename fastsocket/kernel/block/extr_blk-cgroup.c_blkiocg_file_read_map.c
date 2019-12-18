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
struct cgroup_map_cb {int dummy; } ;
struct cgroup {int dummy; } ;
struct cftype {int /*<<< orphan*/  private; } ;
struct blkio_cgroup {int dummy; } ;
typedef  enum blkio_policy_id { ____Placeholder_blkio_policy_id } blkio_policy_id ;

/* Variables and functions */
 int BLKIOFILE_ATTR (int /*<<< orphan*/ ) ; 
 int BLKIOFILE_POLICY (int /*<<< orphan*/ ) ; 
#define  BLKIO_POLICY_PROP 144 
#define  BLKIO_POLICY_THROTL 143 
#define  BLKIO_PROP_avg_queue_size 142 
#define  BLKIO_PROP_dequeue 141 
#define  BLKIO_PROP_empty_time 140 
#define  BLKIO_PROP_group_wait_time 139 
#define  BLKIO_PROP_idle_time 138 
#define  BLKIO_PROP_io_merged 137 
#define  BLKIO_PROP_io_queued 136 
#define  BLKIO_PROP_io_service_bytes 135 
#define  BLKIO_PROP_io_service_time 134 
#define  BLKIO_PROP_io_serviced 133 
#define  BLKIO_PROP_io_wait_time 132 
#define  BLKIO_PROP_sectors 131 
#define  BLKIO_PROP_time 130 
 int /*<<< orphan*/  BLKIO_STAT_AVG_QUEUE_SIZE ; 
 int /*<<< orphan*/  BLKIO_STAT_CPU_SECTORS ; 
 int /*<<< orphan*/  BLKIO_STAT_CPU_SERVICED ; 
 int /*<<< orphan*/  BLKIO_STAT_CPU_SERVICE_BYTES ; 
 int /*<<< orphan*/  BLKIO_STAT_DEQUEUE ; 
 int /*<<< orphan*/  BLKIO_STAT_EMPTY_TIME ; 
 int /*<<< orphan*/  BLKIO_STAT_GROUP_WAIT_TIME ; 
 int /*<<< orphan*/  BLKIO_STAT_IDLE_TIME ; 
 int /*<<< orphan*/  BLKIO_STAT_MERGED ; 
 int /*<<< orphan*/  BLKIO_STAT_QUEUED ; 
 int /*<<< orphan*/  BLKIO_STAT_SERVICE_TIME ; 
 int /*<<< orphan*/  BLKIO_STAT_TIME ; 
 int /*<<< orphan*/  BLKIO_STAT_WAIT_TIME ; 
#define  BLKIO_THROTL_io_service_bytes 129 
#define  BLKIO_THROTL_io_serviced 128 
 int /*<<< orphan*/  BUG () ; 
 int blkio_read_blkg_stats (struct blkio_cgroup*,struct cftype*,struct cgroup_map_cb*,int /*<<< orphan*/ ,int,int) ; 
 struct blkio_cgroup* cgroup_to_blkio_cgroup (struct cgroup*) ; 

__attribute__((used)) static int blkiocg_file_read_map(struct cgroup *cgrp, struct cftype *cft,
				struct cgroup_map_cb *cb)
{
	struct blkio_cgroup *blkcg;
	enum blkio_policy_id plid = BLKIOFILE_POLICY(cft->private);
	int name = BLKIOFILE_ATTR(cft->private);

	blkcg = cgroup_to_blkio_cgroup(cgrp);

	switch(plid) {
	case BLKIO_POLICY_PROP:
		switch(name) {
		case BLKIO_PROP_time:
			return blkio_read_blkg_stats(blkcg, cft, cb,
						BLKIO_STAT_TIME, 0, 0);
		case BLKIO_PROP_sectors:
			return blkio_read_blkg_stats(blkcg, cft, cb,
						BLKIO_STAT_CPU_SECTORS, 0, 1);
		case BLKIO_PROP_io_service_bytes:
			return blkio_read_blkg_stats(blkcg, cft, cb,
					BLKIO_STAT_CPU_SERVICE_BYTES, 1, 1);
		case BLKIO_PROP_io_serviced:
			return blkio_read_blkg_stats(blkcg, cft, cb,
						BLKIO_STAT_CPU_SERVICED, 1, 1);
		case BLKIO_PROP_io_service_time:
			return blkio_read_blkg_stats(blkcg, cft, cb,
						BLKIO_STAT_SERVICE_TIME, 1, 0);
		case BLKIO_PROP_io_wait_time:
			return blkio_read_blkg_stats(blkcg, cft, cb,
						BLKIO_STAT_WAIT_TIME, 1, 0);
		case BLKIO_PROP_io_merged:
			return blkio_read_blkg_stats(blkcg, cft, cb,
						BLKIO_STAT_MERGED, 1, 0);
		case BLKIO_PROP_io_queued:
			return blkio_read_blkg_stats(blkcg, cft, cb,
						BLKIO_STAT_QUEUED, 1, 0);
#ifdef CONFIG_DEBUG_BLK_CGROUP
		case BLKIO_PROP_dequeue:
			return blkio_read_blkg_stats(blkcg, cft, cb,
						BLKIO_STAT_DEQUEUE, 0, 0);
		case BLKIO_PROP_avg_queue_size:
			return blkio_read_blkg_stats(blkcg, cft, cb,
					BLKIO_STAT_AVG_QUEUE_SIZE, 0, 0);
		case BLKIO_PROP_group_wait_time:
			return blkio_read_blkg_stats(blkcg, cft, cb,
					BLKIO_STAT_GROUP_WAIT_TIME, 0, 0);
		case BLKIO_PROP_idle_time:
			return blkio_read_blkg_stats(blkcg, cft, cb,
						BLKIO_STAT_IDLE_TIME, 0, 0);
		case BLKIO_PROP_empty_time:
			return blkio_read_blkg_stats(blkcg, cft, cb,
						BLKIO_STAT_EMPTY_TIME, 0, 0);
#endif
		default:
			BUG();
		}
		break;
	case BLKIO_POLICY_THROTL:
		switch(name){
		case BLKIO_THROTL_io_service_bytes:
			return blkio_read_blkg_stats(blkcg, cft, cb,
						BLKIO_STAT_CPU_SERVICE_BYTES, 1, 1);
		case BLKIO_THROTL_io_serviced:
			return blkio_read_blkg_stats(blkcg, cft, cb,
						BLKIO_STAT_CPU_SERVICED, 1, 1);
		default:
			BUG();
		}
		break;
	default:
		BUG();
	}

	return 0;
}