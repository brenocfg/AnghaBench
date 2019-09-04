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
struct ifnet {int if_eflags; int /*<<< orphan*/  if_poll_update; } ;
typedef  int cqev_t ;

/* Variables and functions */
#define  CLASSQ_EV_LINK_BANDWIDTH 128 
 int IFEF_RXPOLL ; 
 int /*<<< orphan*/  net_rxpoll ; 

void
ifnet_update_rcv(struct ifnet *ifp, cqev_t ev)
{
	switch (ev) {
	case CLASSQ_EV_LINK_BANDWIDTH:
		if (net_rxpoll && (ifp->if_eflags & IFEF_RXPOLL))
			ifp->if_poll_update++;
		break;

	default:
		break;
	}
}