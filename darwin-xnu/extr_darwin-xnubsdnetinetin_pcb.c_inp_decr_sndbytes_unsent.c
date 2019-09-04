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
struct TYPE_2__ {int sb_flags; } ;
struct socket {TYPE_1__ so_snd; scalar_t__ so_pcb; } ;
struct inpcb {struct ifnet* inp_last_outifp; } ;
struct ifnet {scalar_t__ if_sndbyte_unsent; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSAddAtomic64 (scalar_t__,scalar_t__*) ; 
 int SB_SNDBYTE_CNT ; 

inline void
inp_decr_sndbytes_unsent(struct socket *so, int32_t len)
{
	struct inpcb *inp = (struct inpcb *)so->so_pcb;
	struct ifnet *ifp = inp->inp_last_outifp;

	if (so == NULL || !(so->so_snd.sb_flags & SB_SNDBYTE_CNT))
		return;

	if (ifp != NULL) {
		if (ifp->if_sndbyte_unsent >= len)
			OSAddAtomic64(-len, &ifp->if_sndbyte_unsent);
		else
			ifp->if_sndbyte_unsent = 0;
	}
}