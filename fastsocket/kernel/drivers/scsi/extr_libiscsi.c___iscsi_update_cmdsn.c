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
typedef  scalar_t__ uint32_t ;
struct iscsi_session {scalar_t__ exp_cmdsn; scalar_t__ max_cmdsn; TYPE_1__* leadconn; } ;
struct TYPE_2__ {int /*<<< orphan*/  mgmtqueue; int /*<<< orphan*/  cmdqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  iscsi_conn_queue_work (TYPE_1__*) ; 
 scalar_t__ iscsi_sna_lt (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __iscsi_update_cmdsn(struct iscsi_session *session,
				 uint32_t exp_cmdsn, uint32_t max_cmdsn)
{
	/*
	 * standard specifies this check for when to update expected and
	 * max sequence numbers
	 */
	if (iscsi_sna_lt(max_cmdsn, exp_cmdsn - 1))
		return;

	if (exp_cmdsn != session->exp_cmdsn &&
	    !iscsi_sna_lt(exp_cmdsn, session->exp_cmdsn))
		session->exp_cmdsn = exp_cmdsn;

	if (max_cmdsn != session->max_cmdsn &&
	    !iscsi_sna_lt(max_cmdsn, session->max_cmdsn)) {
		session->max_cmdsn = max_cmdsn;
		/*
		 * if the window closed with IO queued, then kick the
		 * xmit thread
		 */
		if (!list_empty(&session->leadconn->cmdqueue) ||
		    !list_empty(&session->leadconn->mgmtqueue))
			iscsi_conn_queue_work(session->leadconn);
	}
}