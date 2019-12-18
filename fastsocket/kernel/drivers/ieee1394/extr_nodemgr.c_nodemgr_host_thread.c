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
struct hpsb_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPSB_VERBOSE (char*) ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 unsigned int get_hpsb_generation (struct hpsb_host*) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  nodemgr_check_irm_capability (struct hpsb_host*,int) ; 
 int /*<<< orphan*/  nodemgr_create_host_dev_files (struct hpsb_host*) ; 
 int /*<<< orphan*/  nodemgr_do_irm_duties (struct hpsb_host*,int) ; 
 int /*<<< orphan*/  nodemgr_node_probe (struct hpsb_host*,unsigned int) ; 
 int /*<<< orphan*/  nodemgr_node_scan (struct hpsb_host*,unsigned int) ; 
 int /*<<< orphan*/  nodemgr_remove_nodes_in_limbo (struct hpsb_host*) ; 
 int /*<<< orphan*/  nodemgr_update_host_dev_links (struct hpsb_host*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_freezable () ; 
 scalar_t__ try_to_freeze () ; 

__attribute__((used)) static int nodemgr_host_thread(void *data)
{
	struct hpsb_host *host = data;
	unsigned int g, generation = 0;
	int i, reset_cycles = 0;

	set_freezable();
	/* Setup our device-model entries */
	nodemgr_create_host_dev_files(host);

	for (;;) {
		/* Sleep until next bus reset */
		set_current_state(TASK_INTERRUPTIBLE);
		if (get_hpsb_generation(host) == generation &&
		    !kthread_should_stop())
			schedule();
		__set_current_state(TASK_RUNNING);

		/* Thread may have been woken up to freeze or to exit */
		if (try_to_freeze())
			continue;
		if (kthread_should_stop())
			goto exit;

		/* Pause for 1/4 second in 1/16 second intervals,
		 * to make sure things settle down. */
		g = get_hpsb_generation(host);
		for (i = 0; i < 4 ; i++) {
			msleep_interruptible(63);
			try_to_freeze();
			if (kthread_should_stop())
				goto exit;

			/* Now get the generation in which the node ID's we collect
			 * are valid.  During the bus scan we will use this generation
			 * for the read transactions, so that if another reset occurs
			 * during the scan the transactions will fail instead of
			 * returning bogus data. */
			generation = get_hpsb_generation(host);

			/* If we get a reset before we are done waiting, then
			 * start the waiting over again */
			if (generation != g)
				g = generation, i = 0;
		}

		if (!nodemgr_check_irm_capability(host, reset_cycles) ||
		    !nodemgr_do_irm_duties(host, reset_cycles)) {
			reset_cycles++;
			continue;
		}
		reset_cycles = 0;

		/* Scan our nodes to get the bus options and create node
		 * entries. This does not do the sysfs stuff, since that
		 * would trigger uevents and such, which is a bad idea at
		 * this point. */
		nodemgr_node_scan(host, generation);

		/* This actually does the full probe, with sysfs
		 * registration. */
		if (!nodemgr_node_probe(host, generation))
			continue;

		/* Update some of our sysfs symlinks */
		nodemgr_update_host_dev_links(host);

		/* Sleep 3 seconds */
		for (i = 3000/200; i; i--) {
			msleep_interruptible(200);
			try_to_freeze();
			if (kthread_should_stop())
				goto exit;

			if (generation != get_hpsb_generation(host))
				break;
		}
		/* Remove nodes which are gone, unless a bus reset happened */
		if (!i)
			nodemgr_remove_nodes_in_limbo(host);
	}
exit:
	HPSB_VERBOSE("NodeMgr: Exiting thread");
	return 0;
}