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
typedef  int u_char ;
struct mibrcvaddr {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int ifi_type; } ;
struct TYPE_4__ {int ifmd_flags; TYPE_1__ ifmd_data; } ;
struct mibif {int /*<<< orphan*/  index; TYPE_2__ mib; } ;

/* Variables and functions */
 int IFF_BROADCAST ; 
#define  IFT_ETHER 131 
#define  IFT_FDDI 130 
#define  IFT_ISO88025 129 
#define  IFT_L2VLAN 128 
 int /*<<< orphan*/  MIBRCVADDR_BCAST ; 
 int /*<<< orphan*/ * mib_find_rcvaddr (int /*<<< orphan*/ ,int*,int) ; 
 struct mibrcvaddr* mib_rcvaddr_create (struct mibif*,int*,int) ; 

__attribute__((used)) static void
check_llbcast(struct mibif *ifp)
{
	static u_char ether_bcast[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
	struct mibrcvaddr *rcv;

	if (!(ifp->mib.ifmd_flags & IFF_BROADCAST))
		return;

	switch (ifp->mib.ifmd_data.ifi_type) {

	  case IFT_ETHER:
	  case IFT_FDDI:
	  case IFT_ISO88025:
	  case IFT_L2VLAN:
		if (mib_find_rcvaddr(ifp->index, ether_bcast, 6) == NULL &&
		    (rcv = mib_rcvaddr_create(ifp, ether_bcast, 6)) != NULL)
			rcv->flags |= MIBRCVADDR_BCAST;
		break;
	}
}