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
struct socket {int so_state; TYPE_1__* so_proto; } ;
struct sockaddr {int dummy; } ;
struct TYPE_4__ {int (* pru_accept ) (struct socket*,struct sockaddr**) ;} ;
struct TYPE_3__ {TYPE_2__* pr_usrreqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_NULL ; 
 int SS_NOFDREF ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  so_update_last_owner_locked (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  so_update_necp_policy (struct socket*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  so_update_policy (struct socket*) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int) ; 
 int stub1 (struct socket*,struct sockaddr**) ; 

int
soacceptlock(struct socket *so, struct sockaddr **nam, int dolock)
{
	int error;

	if (dolock)
		socket_lock(so, 1);

	so_update_last_owner_locked(so, PROC_NULL);
	so_update_policy(so);
#if NECP
	so_update_necp_policy(so, NULL, NULL);
#endif /* NECP */

	if ((so->so_state & SS_NOFDREF) == 0)
		panic("soaccept: !NOFDREF");
	so->so_state &= ~SS_NOFDREF;
	error = (*so->so_proto->pr_usrreqs->pru_accept)(so, nam);

	if (dolock)
		socket_unlock(so, 1);
	return (error);
}