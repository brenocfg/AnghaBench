#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket {int so_state; TYPE_2__* so_proto; } ;
typedef  int /*<<< orphan*/  sae_connid_t ;
typedef  int /*<<< orphan*/  sae_associd_t ;
struct TYPE_4__ {TYPE_1__* pr_usrreqs; } ;
struct TYPE_3__ {int (* pru_disconnectx ) (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int SS_ISDISCONNECTED ; 
 int SS_ISDISCONNECTING ; 
 int /*<<< orphan*/  sflt_notify (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_evt_disconnected ; 
 int stub1 (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sodisconnectxlocked(struct socket *so, sae_associd_t aid, sae_connid_t cid)
{
	int error;

	/*
	 * Call the protocol disconnectx handler; let it handle all
	 * matters related to the connection state of this session.
	 */
	error = (*so->so_proto->pr_usrreqs->pru_disconnectx)(so, aid, cid);
	if (error == 0) {
		/*
		 * The event applies only for the session, not for
		 * the disconnection of individual subflows.
		 */
		if (so->so_state & (SS_ISDISCONNECTING|SS_ISDISCONNECTED))
			sflt_notify(so, sock_evt_disconnected, NULL);
	}
	return (error);
}