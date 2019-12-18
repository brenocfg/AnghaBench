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
struct domain_join_ctxt {int /*<<< orphan*/  yes_resp_map; int /*<<< orphan*/  live_map; } ;
struct dlm_ctxt {int node_num; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  num_joins; int /*<<< orphan*/  dlm_state; int /*<<< orphan*/  domain_map; int /*<<< orphan*/  live_nodes_map; } ;
typedef  enum dlm_query_join_response_code { ____Placeholder_dlm_query_join_response_code } dlm_query_join_response_code ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_CTXT_JOINED ; 
 int DLM_LOCK_RES_OWNER_UNKNOWN ; 
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int JOIN_DISALLOW ; 
 int JOIN_OK ; 
 int O2NM_MAX_NODES ; 
 int /*<<< orphan*/  __dlm_print_nodes (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  __dlm_set_joining_node (struct dlm_ctxt*,int) ; 
 int /*<<< orphan*/  dlm_domain_lock ; 
 int dlm_request_join (struct dlm_ctxt*,int,int*) ; 
 int /*<<< orphan*/  dlm_send_join_asserts (struct dlm_ctxt*,int /*<<< orphan*/ ) ; 
 int dlm_send_join_cancels (struct dlm_ctxt*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ dlm_should_restart_join (struct dlm_ctxt*,struct domain_join_ctxt*,int) ; 
 int find_next_bit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  kfree (struct domain_join_ctxt*) ; 
 struct domain_join_ctxt* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_entry (char*,struct dlm_ctxt*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  o2hb_fill_node_map (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dlm_try_to_join_domain(struct dlm_ctxt *dlm)
{
	int status = 0, tmpstat, node;
	struct domain_join_ctxt *ctxt;
	enum dlm_query_join_response_code response = JOIN_DISALLOW;

	mlog_entry("%p", dlm);

	ctxt = kzalloc(sizeof(*ctxt), GFP_KERNEL);
	if (!ctxt) {
		status = -ENOMEM;
		mlog_errno(status);
		goto bail;
	}

	/* group sem locking should work for us here -- we're already
	 * registered for heartbeat events so filling this should be
	 * atomic wrt getting those handlers called. */
	o2hb_fill_node_map(dlm->live_nodes_map, sizeof(dlm->live_nodes_map));

	spin_lock(&dlm->spinlock);
	memcpy(ctxt->live_map, dlm->live_nodes_map, sizeof(ctxt->live_map));

	__dlm_set_joining_node(dlm, dlm->node_num);

	spin_unlock(&dlm->spinlock);

	node = -1;
	while ((node = find_next_bit(ctxt->live_map, O2NM_MAX_NODES,
				     node + 1)) < O2NM_MAX_NODES) {
		if (node == dlm->node_num)
			continue;

		status = dlm_request_join(dlm, node, &response);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}

		/* Ok, either we got a response or the node doesn't have a
		 * dlm up. */
		if (response == JOIN_OK)
			set_bit(node, ctxt->yes_resp_map);

		if (dlm_should_restart_join(dlm, ctxt, response)) {
			status = -EAGAIN;
			goto bail;
		}
	}

	mlog(0, "Yay, done querying nodes!\n");

	/* Yay, everyone agree's we can join the domain. My domain is
	 * comprised of all nodes who were put in the
	 * yes_resp_map. Copy that into our domain map and send a join
	 * assert message to clean up everyone elses state. */
	spin_lock(&dlm->spinlock);
	memcpy(dlm->domain_map, ctxt->yes_resp_map,
	       sizeof(ctxt->yes_resp_map));
	set_bit(dlm->node_num, dlm->domain_map);
	spin_unlock(&dlm->spinlock);

	dlm_send_join_asserts(dlm, ctxt->yes_resp_map);

	/* Joined state *must* be set before the joining node
	 * information, otherwise the query_join handler may read no
	 * current joiner but a state of NEW and tell joining nodes
	 * we're not in the domain. */
	spin_lock(&dlm_domain_lock);
	dlm->dlm_state = DLM_CTXT_JOINED;
	dlm->num_joins++;
	spin_unlock(&dlm_domain_lock);

bail:
	spin_lock(&dlm->spinlock);
	__dlm_set_joining_node(dlm, DLM_LOCK_RES_OWNER_UNKNOWN);
	if (!status)
		__dlm_print_nodes(dlm);
	spin_unlock(&dlm->spinlock);

	if (ctxt) {
		/* Do we need to send a cancel message to any nodes? */
		if (status < 0) {
			tmpstat = dlm_send_join_cancels(dlm,
							ctxt->yes_resp_map,
							sizeof(ctxt->yes_resp_map));
			if (tmpstat < 0)
				mlog_errno(tmpstat);
		}
		kfree(ctxt);
	}

	mlog(0, "returning %d\n", status);
	return status;
}