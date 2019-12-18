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
struct dlm_mhandle {int dummy; } ;
struct dlm_message {scalar_t__ m_result; } ;
struct dlm_lkb {int lkb_nodeid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_MSG_GRANT ; 
 int create_message (struct dlm_rsb*,struct dlm_lkb*,int,int /*<<< orphan*/ ,struct dlm_message**,struct dlm_mhandle**) ; 
 int /*<<< orphan*/  send_args (struct dlm_rsb*,struct dlm_lkb*,struct dlm_message*) ; 
 int send_message (struct dlm_mhandle*,struct dlm_message*) ; 

__attribute__((used)) static int send_grant(struct dlm_rsb *r, struct dlm_lkb *lkb)
{
	struct dlm_message *ms;
	struct dlm_mhandle *mh;
	int to_nodeid, error;

	to_nodeid = lkb->lkb_nodeid;

	error = create_message(r, lkb, to_nodeid, DLM_MSG_GRANT, &ms, &mh);
	if (error)
		goto out;

	send_args(r, lkb, ms);

	ms->m_result = 0;

	error = send_message(mh, ms);
 out:
	return error;
}