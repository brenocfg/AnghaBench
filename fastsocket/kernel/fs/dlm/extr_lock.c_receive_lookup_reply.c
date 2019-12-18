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
struct dlm_rsb {int res_nodeid; scalar_t__ res_first_lkid; } ;
struct dlm_message {int m_nodeid; int /*<<< orphan*/  m_lkid; } ;
struct dlm_ls {int dummy; } ;
struct dlm_lkb {int /*<<< orphan*/  lkb_flags; int /*<<< orphan*/  lkb_id; struct dlm_rsb* lkb_resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_MSG_LOOKUP_REPLY ; 
 int /*<<< orphan*/  _request_lock (struct dlm_rsb*,struct dlm_lkb*) ; 
 int dlm_our_nodeid () ; 
 int /*<<< orphan*/  dlm_put_lkb (struct dlm_lkb*) ; 
 int find_lkb (struct dlm_ls*,int /*<<< orphan*/ ,struct dlm_lkb**) ; 
 int /*<<< orphan*/  hold_rsb (struct dlm_rsb*) ; 
 scalar_t__ is_overlap (struct dlm_lkb*) ; 
 int /*<<< orphan*/  lock_rsb (struct dlm_rsb*) ; 
 int /*<<< orphan*/  log_debug (struct dlm_ls*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_error (struct dlm_ls*,char*) ; 
 int /*<<< orphan*/  process_lookup_list (struct dlm_rsb*) ; 
 int /*<<< orphan*/  put_rsb (struct dlm_rsb*) ; 
 int /*<<< orphan*/  queue_cast_overlap (struct dlm_rsb*,struct dlm_lkb*) ; 
 int remove_from_waiters (struct dlm_lkb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unhold_lkb (struct dlm_lkb*) ; 
 int /*<<< orphan*/  unlock_rsb (struct dlm_rsb*) ; 

__attribute__((used)) static void receive_lookup_reply(struct dlm_ls *ls, struct dlm_message *ms)
{
	struct dlm_lkb *lkb;
	struct dlm_rsb *r;
	int error, ret_nodeid;

	error = find_lkb(ls, ms->m_lkid, &lkb);
	if (error) {
		log_error(ls, "receive_lookup_reply no lkb");
		return;
	}

	/* ms->m_result is the value returned by dlm_dir_lookup on dir node
	   FIXME: will a non-zero error ever be returned? */

	r = lkb->lkb_resource;
	hold_rsb(r);
	lock_rsb(r);

	error = remove_from_waiters(lkb, DLM_MSG_LOOKUP_REPLY);
	if (error)
		goto out;

	ret_nodeid = ms->m_nodeid;
	if (ret_nodeid == dlm_our_nodeid()) {
		r->res_nodeid = 0;
		ret_nodeid = 0;
		r->res_first_lkid = 0;
	} else {
		/* set_master() will copy res_nodeid to lkb_nodeid */
		r->res_nodeid = ret_nodeid;
	}

	if (is_overlap(lkb)) {
		log_debug(ls, "receive_lookup_reply %x unlock %x",
			  lkb->lkb_id, lkb->lkb_flags);
		queue_cast_overlap(r, lkb);
		unhold_lkb(lkb); /* undoes create_lkb() */
		goto out_list;
	}

	_request_lock(r, lkb);

 out_list:
	if (!ret_nodeid)
		process_lookup_list(r);
 out:
	unlock_rsb(r);
	put_rsb(r);
	dlm_put_lkb(lkb);
}