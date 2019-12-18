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
struct ifnet {int if_type; } ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
#define  IFT_ARCNET 137 
#define  IFT_BRIDGE 136 
#define  IFT_CARP 135 
#define  IFT_ETHER 134 
#define  IFT_FDDI 133 
#define  IFT_IEEE1394 132 
#define  IFT_IEEE80211 131 
#define  IFT_IEEE8023ADLAG 130 
#define  IFT_ISO88025 129 
#define  IFT_L2VLAN 128 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 

caddr_t
nd6_ifptomac(
	struct ifnet *ifp)
{
	switch (ifp->if_type) {
	case IFT_ARCNET:
	case IFT_ETHER:
	case IFT_IEEE8023ADLAG:
	case IFT_FDDI:
	case IFT_IEEE1394:
#ifdef IFT_L2VLAN
	case IFT_L2VLAN:
#endif
#ifdef IFT_IEEE80211
	case IFT_IEEE80211:
#endif
#ifdef IFT_CARP
	case IFT_CARP:
#endif
	case IFT_BRIDGE:
	case IFT_ISO88025:
		return ((caddr_t)IF_LLADDR(ifp));
	default:
		return NULL;
	}
}