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
typedef  scalar_t__ uint64_t ;
struct cgroup_map_cb {int /*<<< orphan*/  (* fill ) (struct cgroup_map_cb*,char*,scalar_t__) ;} ;
struct TYPE_2__ {scalar_t__** stat_arr; scalar_t__ dequeue; scalar_t__ empty_time; scalar_t__ idle_time; scalar_t__ group_wait_time; scalar_t__ avg_queue_size_samples; scalar_t__ avg_queue_size_sum; scalar_t__ time; } ;
struct blkio_group {TYPE_1__ stats; } ;
typedef  enum stat_type { ____Placeholder_stat_type } stat_type ;
typedef  enum stat_sub_type { ____Placeholder_stat_sub_type } stat_sub_type ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int BLKIO_STAT_AVG_QUEUE_SIZE ; 
 int BLKIO_STAT_DEQUEUE ; 
 int BLKIO_STAT_EMPTY_TIME ; 
 int BLKIO_STAT_GROUP_WAIT_TIME ; 
 int BLKIO_STAT_IDLE_TIME ; 
 size_t BLKIO_STAT_READ ; 
 int BLKIO_STAT_TIME ; 
 int BLKIO_STAT_TOTAL ; 
 size_t BLKIO_STAT_WRITE ; 
 int MAX_KEY_LEN ; 
 scalar_t__ blkio_fill_stat (char*,int,scalar_t__,struct cgroup_map_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkio_get_key_name (int,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  do_div (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct cgroup_map_cb*,char*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct cgroup_map_cb*,char*,scalar_t__) ; 

__attribute__((used)) static uint64_t blkio_get_stat(struct blkio_group *blkg,
		struct cgroup_map_cb *cb, dev_t dev, enum stat_type type)
{
	uint64_t disk_total;
	char key_str[MAX_KEY_LEN];
	enum stat_sub_type sub_type;

	if (type == BLKIO_STAT_TIME)
		return blkio_fill_stat(key_str, MAX_KEY_LEN - 1,
					blkg->stats.time, cb, dev);
#ifdef CONFIG_DEBUG_BLK_CGROUP
	if (type == BLKIO_STAT_AVG_QUEUE_SIZE) {
		uint64_t sum = blkg->stats.avg_queue_size_sum;
		uint64_t samples = blkg->stats.avg_queue_size_samples;
		if (samples)
			do_div(sum, samples);
		else
			sum = 0;
		return blkio_fill_stat(key_str, MAX_KEY_LEN - 1, sum, cb, dev);
	}
	if (type == BLKIO_STAT_GROUP_WAIT_TIME)
		return blkio_fill_stat(key_str, MAX_KEY_LEN - 1,
					blkg->stats.group_wait_time, cb, dev);
	if (type == BLKIO_STAT_IDLE_TIME)
		return blkio_fill_stat(key_str, MAX_KEY_LEN - 1,
					blkg->stats.idle_time, cb, dev);
	if (type == BLKIO_STAT_EMPTY_TIME)
		return blkio_fill_stat(key_str, MAX_KEY_LEN - 1,
					blkg->stats.empty_time, cb, dev);
	if (type == BLKIO_STAT_DEQUEUE)
		return blkio_fill_stat(key_str, MAX_KEY_LEN - 1,
					blkg->stats.dequeue, cb, dev);
#endif

	for (sub_type = BLKIO_STAT_READ; sub_type < BLKIO_STAT_TOTAL;
			sub_type++) {
		blkio_get_key_name(sub_type, dev, key_str, MAX_KEY_LEN, false);
		cb->fill(cb, key_str, blkg->stats.stat_arr[type][sub_type]);
	}
	disk_total = blkg->stats.stat_arr[type][BLKIO_STAT_READ] +
			blkg->stats.stat_arr[type][BLKIO_STAT_WRITE];
	blkio_get_key_name(BLKIO_STAT_TOTAL, dev, key_str, MAX_KEY_LEN, false);
	cb->fill(cb, key_str, disk_total);
	return disk_total;
}