#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rcom_lock {void* rl_result; int /*<<< orphan*/  rl_lkid; void* rl_remid; int /*<<< orphan*/  rl_status; int /*<<< orphan*/  rl_namelen; int /*<<< orphan*/  rl_name; scalar_t__ rl_parent_lkid; } ;
struct dlm_rsb {int /*<<< orphan*/  res_convertqueue; int /*<<< orphan*/  res_waitqueue; } ;
struct TYPE_2__ {int /*<<< orphan*/  h_nodeid; } ;
struct dlm_rcom {TYPE_1__ rc_header; scalar_t__ rc_buf; } ;
struct dlm_ls {int dummy; } ;
struct dlm_lkb {int lkb_id; } ;

/* Variables and functions */
 int EEXIST ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  RSB_RECOVER_GRANT ; 
 int /*<<< orphan*/  R_MASTER ; 
 int /*<<< orphan*/  __put_lkb (struct dlm_ls*,struct dlm_lkb*) ; 
 int /*<<< orphan*/  add_lkb (struct dlm_rsb*,struct dlm_lkb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attach_lkb (struct dlm_rsb*,struct dlm_lkb*) ; 
 void* cpu_to_le32 (int) ; 
 int create_lkb (struct dlm_ls*,struct dlm_lkb**) ; 
 int find_rsb (struct dlm_ls*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_rsb**) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rsb (struct dlm_rsb*) ; 
 int /*<<< orphan*/  log_debug (struct dlm_ls*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_rsb (struct dlm_rsb*) ; 
 int receive_rcom_lock_args (struct dlm_ls*,struct dlm_lkb*,struct dlm_rsb*,struct dlm_rcom*) ; 
 int /*<<< orphan*/  rsb_set_flag (struct dlm_rsb*,int /*<<< orphan*/ ) ; 
 struct dlm_lkb* search_remid (struct dlm_rsb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_rsb (struct dlm_rsb*) ; 

int dlm_recover_master_copy(struct dlm_ls *ls, struct dlm_rcom *rc)
{
	struct rcom_lock *rl = (struct rcom_lock *) rc->rc_buf;
	struct dlm_rsb *r;
	struct dlm_lkb *lkb;
	int error;

	if (rl->rl_parent_lkid) {
		error = -EOPNOTSUPP;
		goto out;
	}

	error = find_rsb(ls, rl->rl_name, le16_to_cpu(rl->rl_namelen),
			 R_MASTER, &r);
	if (error)
		goto out;

	lock_rsb(r);

	lkb = search_remid(r, rc->rc_header.h_nodeid, le32_to_cpu(rl->rl_lkid));
	if (lkb) {
		error = -EEXIST;
		goto out_remid;
	}

	error = create_lkb(ls, &lkb);
	if (error)
		goto out_unlock;

	error = receive_rcom_lock_args(ls, lkb, r, rc);
	if (error) {
		__put_lkb(ls, lkb);
		goto out_unlock;
	}

	attach_lkb(r, lkb);
	add_lkb(r, lkb, rl->rl_status);
	error = 0;

	if (!list_empty(&r->res_waitqueue) || !list_empty(&r->res_convertqueue))
		rsb_set_flag(r, RSB_RECOVER_GRANT);

 out_remid:
	/* this is the new value returned to the lock holder for
	   saving in its process-copy lkb */
	rl->rl_remid = cpu_to_le32(lkb->lkb_id);

 out_unlock:
	unlock_rsb(r);
	put_rsb(r);
 out:
	if (error)
		log_debug(ls, "recover_master_copy %d %x", error,
			  le32_to_cpu(rl->rl_lkid));
	rl->rl_result = cpu_to_le32(error);
	return error;
}