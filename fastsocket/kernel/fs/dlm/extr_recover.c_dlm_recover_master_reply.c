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
struct dlm_rsb {int dummy; } ;
struct dlm_rcom {int rc_result; scalar_t__ rc_id; } ;
struct dlm_ls {int /*<<< orphan*/  ls_wait_general; } ;

/* Variables and functions */
 int dlm_our_nodeid () ; 
 int /*<<< orphan*/  log_error (struct dlm_ls*,char*,unsigned long long) ; 
 int /*<<< orphan*/  recover_list_del (struct dlm_rsb*) ; 
 scalar_t__ recover_list_empty (struct dlm_ls*) ; 
 struct dlm_rsb* recover_list_find (struct dlm_ls*,scalar_t__) ; 
 int /*<<< orphan*/  set_new_master (struct dlm_rsb*,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int dlm_recover_master_reply(struct dlm_ls *ls, struct dlm_rcom *rc)
{
	struct dlm_rsb *r;
	int nodeid;

	r = recover_list_find(ls, rc->rc_id);
	if (!r) {
		log_error(ls, "dlm_recover_master_reply no id %llx",
			  (unsigned long long)rc->rc_id);
		goto out;
	}

	nodeid = rc->rc_result;
	if (nodeid == dlm_our_nodeid())
		nodeid = 0;

	set_new_master(r, nodeid);
	recover_list_del(r);

	if (recover_list_empty(ls))
		wake_up(&ls->ls_wait_general);
 out:
	return 0;
}