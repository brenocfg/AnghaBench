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
struct TYPE_2__ {int /*<<< orphan*/  h_nodeid; } ;
struct dlm_message {int /*<<< orphan*/  m_remid; TYPE_1__ m_header; } ;
struct dlm_ls {int dummy; } ;
struct dlm_lkb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _receive_cancel_reply (struct dlm_lkb*,struct dlm_message*) ; 
 int /*<<< orphan*/  dlm_put_lkb (struct dlm_lkb*) ; 
 int find_lkb (struct dlm_ls*,int /*<<< orphan*/ ,struct dlm_lkb**) ; 
 int /*<<< orphan*/  log_debug (struct dlm_ls*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void receive_cancel_reply(struct dlm_ls *ls, struct dlm_message *ms)
{
	struct dlm_lkb *lkb;
	int error;

	error = find_lkb(ls, ms->m_remid, &lkb);
	if (error) {
		log_debug(ls, "receive_cancel_reply from %d no lkb %x",
			  ms->m_header.h_nodeid, ms->m_remid);
		return;
	}

	_receive_cancel_reply(lkb, ms);
	dlm_put_lkb(lkb);
}