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
struct dlm_exit_domain {int /*<<< orphan*/  node_idx; } ;
struct dlm_ctxt {int /*<<< orphan*/  key; int /*<<< orphan*/  node_num; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  leave_msg ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_EXIT_DOMAIN_MSG ; 
 int /*<<< orphan*/  memset (struct dlm_exit_domain*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,...) ; 
 int o2net_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_exit_domain*,int,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dlm_send_one_domain_exit(struct dlm_ctxt *dlm,
				    unsigned int node)
{
	int status;
	struct dlm_exit_domain leave_msg;

	mlog(0, "Asking node %u if we can leave the domain %s me = %u\n",
		  node, dlm->name, dlm->node_num);

	memset(&leave_msg, 0, sizeof(leave_msg));
	leave_msg.node_idx = dlm->node_num;

	status = o2net_send_message(DLM_EXIT_DOMAIN_MSG, dlm->key,
				    &leave_msg, sizeof(leave_msg), node,
				    NULL);

	mlog(0, "status return %d from o2net_send_message\n", status);

	return status;
}