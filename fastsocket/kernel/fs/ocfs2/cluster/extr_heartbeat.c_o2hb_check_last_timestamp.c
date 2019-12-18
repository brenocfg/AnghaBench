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
struct o2hb_region {struct o2hb_disk_slot* hr_slots; } ;
struct o2hb_disk_slot {scalar_t__ ds_last_time; struct o2hb_disk_heartbeat_block* ds_raw_block; } ;
struct o2hb_disk_heartbeat_block {int /*<<< orphan*/  hb_seq; } ;

/* Variables and functions */
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int o2nm_this_node () ; 

__attribute__((used)) static int o2hb_check_last_timestamp(struct o2hb_region *reg)
{
	int node_num, ret;
	struct o2hb_disk_slot *slot;
	struct o2hb_disk_heartbeat_block *hb_block;

	node_num = o2nm_this_node();

	ret = 1;
	slot = &reg->hr_slots[node_num];
	/* Don't check on our 1st timestamp */
	if (slot->ds_last_time) {
		hb_block = slot->ds_raw_block;

		if (le64_to_cpu(hb_block->hb_seq) != slot->ds_last_time)
			ret = 0;
	}

	return ret;
}