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
typedef  int u_int16_t ;
struct inpcb {TYPE_1__* inp_socket; struct ifnet* inp_last_outifp; } ;
struct ifnet {int dummy; } ;
struct TYPE_2__ {int so_flags1; } ;

/* Variables and functions */
 int NSTAT_IFNET_IS_CELLULAR ; 
 int NSTAT_IFNET_IS_UNKNOWN_TYPE ; 
 int NSTAT_IFNET_VIA_CELLFALLBACK ; 
 int SOF1_CELLFALLBACK ; 
 int nstat_ifnet_to_flags (struct ifnet*) ; 

__attribute__((used)) static u_int16_t
nstat_inpcb_to_flags(
	const struct inpcb *inp)
{
	u_int16_t flags = 0;

	if ((inp != NULL ) && (inp->inp_last_outifp != NULL))
	{
		struct ifnet *ifp = inp->inp_last_outifp;
		flags = nstat_ifnet_to_flags(ifp);

		if (flags & NSTAT_IFNET_IS_CELLULAR)
		{
			if (inp->inp_socket != NULL &&
			    (inp->inp_socket->so_flags1 & SOF1_CELLFALLBACK))
				flags |= NSTAT_IFNET_VIA_CELLFALLBACK;
		}
	}
	else
	{
		flags = NSTAT_IFNET_IS_UNKNOWN_TYPE;
	}

	return flags;
}