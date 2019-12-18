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
struct o2hb_region {int /*<<< orphan*/  hr_steady_iterations; int /*<<< orphan*/  hr_dev_name; int /*<<< orphan*/ * hr_slots; int /*<<< orphan*/  hr_generation; } ;
struct o2hb_bio_wait_ctxt {int wc_error; } ;
typedef  int /*<<< orphan*/  configured_nodes ;

/* Variables and functions */
 int BITS_TO_LONGS (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  ML_NOTICE ; 
 int O2NM_MAX_NODES ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int find_next_bit (unsigned long*,int,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  o2hb_arm_write_timeout (struct o2hb_region*) ; 
 int /*<<< orphan*/  o2hb_check_last_timestamp (struct o2hb_region*) ; 
 int o2hb_check_slot (struct o2hb_region*,int /*<<< orphan*/ *) ; 
 int o2hb_highest_node (unsigned long*,int) ; 
 int o2hb_issue_node_write (struct o2hb_region*,struct o2hb_bio_wait_ctxt*) ; 
 int /*<<< orphan*/  o2hb_prepare_block (struct o2hb_region*,int /*<<< orphan*/ ) ; 
 int o2hb_read_slots (struct o2hb_region*,int) ; 
 int /*<<< orphan*/  o2hb_steady_queue ; 
 int /*<<< orphan*/  o2hb_wait_on_io (struct o2hb_region*,struct o2hb_bio_wait_ctxt*) ; 
 int o2nm_configured_node_map (unsigned long*,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int o2hb_do_disk_heartbeat(struct o2hb_region *reg)
{
	int i, ret, highest_node, change = 0;
	unsigned long configured_nodes[BITS_TO_LONGS(O2NM_MAX_NODES)];
	struct o2hb_bio_wait_ctxt write_wc;

	ret = o2nm_configured_node_map(configured_nodes,
				       sizeof(configured_nodes));
	if (ret) {
		mlog_errno(ret);
		return ret;
	}

	highest_node = o2hb_highest_node(configured_nodes, O2NM_MAX_NODES);
	if (highest_node >= O2NM_MAX_NODES) {
		mlog(ML_NOTICE, "ocfs2_heartbeat: no configured nodes found!\n");
		return -EINVAL;
	}

	/* No sense in reading the slots of nodes that don't exist
	 * yet. Of course, if the node definitions have holes in them
	 * then we're reading an empty slot anyway... Consider this
	 * best-effort. */
	ret = o2hb_read_slots(reg, highest_node + 1);
	if (ret < 0) {
		mlog_errno(ret);
		return ret;
	}

	/* With an up to date view of the slots, we can check that no
	 * other node has been improperly configured to heartbeat in
	 * our slot. */
	if (!o2hb_check_last_timestamp(reg))
		mlog(ML_ERROR, "Device \"%s\": another node is heartbeating "
		     "in our slot!\n", reg->hr_dev_name);

	/* fill in the proper info for our next heartbeat */
	o2hb_prepare_block(reg, reg->hr_generation);

	/* And fire off the write. Note that we don't wait on this I/O
	 * until later. */
	ret = o2hb_issue_node_write(reg, &write_wc);
	if (ret < 0) {
		mlog_errno(ret);
		return ret;
	}

	i = -1;
	while((i = find_next_bit(configured_nodes, O2NM_MAX_NODES, i + 1)) < O2NM_MAX_NODES) {

		change |= o2hb_check_slot(reg, &reg->hr_slots[i]);
	}

	/*
	 * We have to be sure we've advertised ourselves on disk
	 * before we can go to steady state.  This ensures that
	 * people we find in our steady state have seen us.
	 */
	o2hb_wait_on_io(reg, &write_wc);
	if (write_wc.wc_error) {
		/* Do not re-arm the write timeout on I/O error - we
		 * can't be sure that the new block ever made it to
		 * disk */
		mlog(ML_ERROR, "Write error %d on device \"%s\"\n",
		     write_wc.wc_error, reg->hr_dev_name);
		return write_wc.wc_error;
	}

	o2hb_arm_write_timeout(reg);

	/* let the person who launched us know when things are steady */
	if (!change && (atomic_read(&reg->hr_steady_iterations) != 0)) {
		if (atomic_dec_and_test(&reg->hr_steady_iterations))
			wake_up(&o2hb_steady_queue);
	}

	return 0;
}