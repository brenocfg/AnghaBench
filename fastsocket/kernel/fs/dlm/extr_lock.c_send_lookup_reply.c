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
struct dlm_rsb {int dummy; } ;
struct dlm_mhandle {int dummy; } ;
struct TYPE_2__ {int h_nodeid; } ;
struct dlm_message {int m_result; int m_nodeid; int /*<<< orphan*/  m_lkid; TYPE_1__ m_header; } ;
struct dlm_ls {struct dlm_rsb ls_stub_rsb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_MSG_LOOKUP_REPLY ; 
 int create_message (struct dlm_rsb*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct dlm_message**,struct dlm_mhandle**) ; 
 int send_message (struct dlm_mhandle*,struct dlm_message*) ; 

__attribute__((used)) static int send_lookup_reply(struct dlm_ls *ls, struct dlm_message *ms_in,
			     int ret_nodeid, int rv)
{
	struct dlm_rsb *r = &ls->ls_stub_rsb;
	struct dlm_message *ms;
	struct dlm_mhandle *mh;
	int error, nodeid = ms_in->m_header.h_nodeid;

	error = create_message(r, NULL, nodeid, DLM_MSG_LOOKUP_REPLY, &ms, &mh);
	if (error)
		goto out;

	ms->m_lkid = ms_in->m_lkid;
	ms->m_result = rv;
	ms->m_nodeid = ret_nodeid;

	error = send_message(mh, ms);
 out:
	return error;
}