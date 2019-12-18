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
struct bnx2fc_els_cb_arg {struct bnx2fc_cmd* aborted_io_req; struct bnx2fc_cmd* io_req; } ;
struct bnx2fc_cmd {scalar_t__ on_active_queue; int /*<<< orphan*/  link; int /*<<< orphan*/  xid; int /*<<< orphan*/  req_flags; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2FC_ELS_DBG (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  BNX2FC_FLAG_ELS_TIMEOUT ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  bnx2fc_cmd_release ; 
 int bnx2fc_initiate_cleanup (struct bnx2fc_cmd*) ; 
 int /*<<< orphan*/  kfree (struct bnx2fc_els_cb_arg*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnx2fc_rrq_compl(struct bnx2fc_els_cb_arg *cb_arg)
{
	struct bnx2fc_cmd *orig_io_req;
	struct bnx2fc_cmd *rrq_req;
	int rc = 0;

	BUG_ON(!cb_arg);
	rrq_req = cb_arg->io_req;
	orig_io_req = cb_arg->aborted_io_req;
	BUG_ON(!orig_io_req);
	BNX2FC_ELS_DBG("rrq_compl: orig xid = 0x%x, rrq_xid = 0x%x\n",
		   orig_io_req->xid, rrq_req->xid);

	kref_put(&orig_io_req->refcount, bnx2fc_cmd_release);

	if (test_and_clear_bit(BNX2FC_FLAG_ELS_TIMEOUT, &rrq_req->req_flags)) {
		/*
		 * els req is timed out. cleanup the IO with FW and
		 * drop the completion. Remove from active_cmd_queue.
		 */
		BNX2FC_ELS_DBG("rrq xid - 0x%x timed out, clean it up\n",
			   rrq_req->xid);

		if (rrq_req->on_active_queue) {
			list_del_init(&rrq_req->link);
			rrq_req->on_active_queue = 0;
			rc = bnx2fc_initiate_cleanup(rrq_req);
			BUG_ON(rc);
		}
	}
	kfree(cb_arg);
}