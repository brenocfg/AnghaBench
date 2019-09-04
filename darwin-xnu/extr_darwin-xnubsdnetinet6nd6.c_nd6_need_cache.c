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

/* Variables and functions */
#define  IFT_ARCNET 137 
#define  IFT_BRIDGE 136 
#define  IFT_CELLULAR 135 
#define  IFT_ETHER 134 
#define  IFT_FDDI 133 
#define  IFT_GIF 132 
#define  IFT_IEEE1394 131 
#define  IFT_IEEE8023ADLAG 130 
#define  IFT_L2VLAN 129 
#define  IFT_PPP 128 

int
nd6_need_cache(struct ifnet *ifp)
{
	/*
	 * XXX: we currently do not make neighbor cache on any interface
	 * other than ARCnet, Ethernet, FDDI and GIF.
	 *
	 * RFC2893 says:
	 * - unidirectional tunnels needs no ND
	 */
	switch (ifp->if_type) {
	case IFT_ARCNET:
	case IFT_ETHER:
	case IFT_FDDI:
	case IFT_IEEE1394:
	case IFT_L2VLAN:
	case IFT_IEEE8023ADLAG:
#if IFT_IEEE80211
	case IFT_IEEE80211:
#endif
	case IFT_GIF:		/* XXX need more cases? */
	case IFT_PPP:
#if IFT_TUNNEL
	case IFT_TUNNEL:
#endif
	case IFT_BRIDGE:
	case IFT_CELLULAR:
		return (1);
	default:
		return (0);
	}
}