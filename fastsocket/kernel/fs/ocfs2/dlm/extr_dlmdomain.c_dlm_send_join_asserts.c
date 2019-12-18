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
struct dlm_ctxt {int node_num; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  live_nodes_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_DOMAIN_BACKOFF_MS ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int O2NM_MAX_NODES ; 
 int dlm_send_one_join_assert (struct dlm_ctxt*,int) ; 
 int find_next_bit (unsigned long*,int,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dlm_send_join_asserts(struct dlm_ctxt *dlm,
				  unsigned long *node_map)
{
	int status, node, live;

	status = 0;
	node = -1;
	while ((node = find_next_bit(node_map, O2NM_MAX_NODES,
				     node + 1)) < O2NM_MAX_NODES) {
		if (node == dlm->node_num)
			continue;

		do {
			/* It is very important that this message be
			 * received so we spin until either the node
			 * has died or it gets the message. */
			status = dlm_send_one_join_assert(dlm, node);

			spin_lock(&dlm->spinlock);
			live = test_bit(node, dlm->live_nodes_map);
			spin_unlock(&dlm->spinlock);

			if (status) {
				mlog(ML_ERROR, "Error return %d asserting "
				     "join on node %d\n", status, node);

				/* give us some time between errors... */
				if (live)
					msleep(DLM_DOMAIN_BACKOFF_MS);
			}
		} while (status && live);
	}
}