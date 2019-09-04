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
struct socket {int so_state; struct protosw* so_proto; } ;
struct protosw {TYPE_1__* pr_usrreqs; } ;
struct TYPE_2__ {int (* pru_shutdown ) (struct socket*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FNC_SOSHUTDOWN ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  EV_RCLOSED ; 
 int /*<<< orphan*/  EV_WCLOSED ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SHUT_RD ; 
 int SHUT_WR ; 
 int SS_CANTRCVMORE ; 
 int SS_CANTSENDMORE ; 
 int /*<<< orphan*/  postevent (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sflt_notify (struct socket*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sock_evt_shutdown ; 
 int /*<<< orphan*/  sorflush (struct socket*) ; 
 int stub1 (struct socket*) ; 

int
soshutdownlock_final(struct socket *so, int how)
{
	struct protosw *pr = so->so_proto;
	int error = 0;

	sflt_notify(so, sock_evt_shutdown, &how);

	if (how != SHUT_WR) {
		if ((so->so_state & SS_CANTRCVMORE) != 0) {
			/* read already shut down */
			error = ENOTCONN;
			goto done;
		}
		sorflush(so);
		postevent(so, 0, EV_RCLOSED);
	}
	if (how != SHUT_RD) {
		if ((so->so_state & SS_CANTSENDMORE) != 0) {
			/* write already shut down */
			error = ENOTCONN;
			goto done;
		}
		error = (*pr->pr_usrreqs->pru_shutdown)(so);
		postevent(so, 0, EV_WCLOSED);
	}
done:
	KERNEL_DEBUG(DBG_FNC_SOSHUTDOWN, how, 1, 0, 0, 0);
	return (error);
}