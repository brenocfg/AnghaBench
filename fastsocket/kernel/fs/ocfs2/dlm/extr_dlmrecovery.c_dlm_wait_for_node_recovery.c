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
typedef  int /*<<< orphan*/  u8 ;
struct dlm_ctxt {int /*<<< orphan*/  dlm_reco_thread_wq; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dlm_is_node_recovered (struct dlm_ctxt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int dlm_wait_for_node_recovery(struct dlm_ctxt *dlm, u8 node, int timeout)
{
	if (timeout) {
		mlog(0, "%s: waiting %dms for notification of "
		     "recovery of node %u\n", dlm->name, timeout, node);
		wait_event_timeout(dlm->dlm_reco_thread_wq,
			   dlm_is_node_recovered(dlm, node),
			   msecs_to_jiffies(timeout));
	} else {
		mlog(0, "%s: waiting indefinitely for notification "
		     "of recovery of node %u\n", dlm->name, node);
		wait_event(dlm->dlm_reco_thread_wq,
			   dlm_is_node_recovered(dlm, node));
	}
	/* for now, return 0 */
	return 0;
}