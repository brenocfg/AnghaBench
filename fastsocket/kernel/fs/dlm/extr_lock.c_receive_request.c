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
struct dlm_message {int /*<<< orphan*/  m_extra; } ;
struct dlm_lkb {int /*<<< orphan*/  lkb_flags; } ;
struct dlm_ls {struct dlm_lkb ls_stub_lkb; struct dlm_rsb ls_stub_rsb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_IFL_MSTCPY ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  R_MASTER ; 
 int /*<<< orphan*/  __put_lkb (struct dlm_ls*,struct dlm_lkb*) ; 
 int /*<<< orphan*/  attach_lkb (struct dlm_rsb*,struct dlm_lkb*) ; 
 int create_lkb (struct dlm_ls*,struct dlm_lkb**) ; 
 int /*<<< orphan*/  dlm_put_lkb (struct dlm_lkb*) ; 
 int do_request (struct dlm_rsb*,struct dlm_lkb*) ; 
 int /*<<< orphan*/  do_request_effects (struct dlm_rsb*,struct dlm_lkb*,int) ; 
 int find_rsb (struct dlm_ls*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct dlm_rsb**) ; 
 int /*<<< orphan*/  lock_rsb (struct dlm_rsb*) ; 
 int /*<<< orphan*/  put_rsb (struct dlm_rsb*) ; 
 int receive_extralen (struct dlm_message*) ; 
 int /*<<< orphan*/  receive_flags (struct dlm_lkb*,struct dlm_message*) ; 
 int receive_request_args (struct dlm_ls*,struct dlm_lkb*,struct dlm_message*) ; 
 int /*<<< orphan*/  send_request_reply (struct dlm_rsb*,struct dlm_lkb*,int) ; 
 int /*<<< orphan*/  setup_stub_lkb (struct dlm_ls*,struct dlm_message*) ; 
 int /*<<< orphan*/  unlock_rsb (struct dlm_rsb*) ; 

__attribute__((used)) static void receive_request(struct dlm_ls *ls, struct dlm_message *ms)
{
	struct dlm_lkb *lkb;
	struct dlm_rsb *r;
	int error, namelen;

	error = create_lkb(ls, &lkb);
	if (error)
		goto fail;

	receive_flags(lkb, ms);
	lkb->lkb_flags |= DLM_IFL_MSTCPY;
	error = receive_request_args(ls, lkb, ms);
	if (error) {
		__put_lkb(ls, lkb);
		goto fail;
	}

	namelen = receive_extralen(ms);

	error = find_rsb(ls, ms->m_extra, namelen, R_MASTER, &r);
	if (error) {
		__put_lkb(ls, lkb);
		goto fail;
	}

	lock_rsb(r);

	attach_lkb(r, lkb);
	error = do_request(r, lkb);
	send_request_reply(r, lkb, error);
	do_request_effects(r, lkb, error);

	unlock_rsb(r);
	put_rsb(r);

	if (error == -EINPROGRESS)
		error = 0;
	if (error)
		dlm_put_lkb(lkb);
	return;

 fail:
	setup_stub_lkb(ls, ms);
	send_request_reply(&ls->ls_stub_rsb, &ls->ls_stub_lkb, error);
}