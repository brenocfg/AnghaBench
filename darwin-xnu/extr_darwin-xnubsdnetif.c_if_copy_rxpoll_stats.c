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
struct ifnet {int if_eflags; TYPE_1__* if_inp; } ;
struct if_rxpoll_stats {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pstats; } ;

/* Variables and functions */
 int IFEF_RXPOLL ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,struct if_rxpoll_stats*,int) ; 
 int /*<<< orphan*/  bzero (struct if_rxpoll_stats*,int) ; 
 int /*<<< orphan*/  ifnet_decr_iorefcnt (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_is_attached (struct ifnet*,int) ; 

void
if_copy_rxpoll_stats(struct ifnet *ifp, struct if_rxpoll_stats *if_rs)
{
	bzero(if_rs, sizeof (*if_rs));
	if (!(ifp->if_eflags & IFEF_RXPOLL) || !ifnet_is_attached(ifp, 1))
		return;

	/* by now, ifnet will stay attached so if_inp must be valid */
	VERIFY(ifp->if_inp != NULL);
	bcopy(&ifp->if_inp->pstats, if_rs, sizeof (*if_rs));

	/* Release the IO refcnt */
	ifnet_decr_iorefcnt(ifp);
}