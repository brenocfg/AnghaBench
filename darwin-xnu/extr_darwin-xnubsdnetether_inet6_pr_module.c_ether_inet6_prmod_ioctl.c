#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct TYPE_7__ {int /*<<< orphan*/  sa_data; } ;
struct ifreq {TYPE_1__ ifr_addr; } ;
typedef  int /*<<< orphan*/  protocol_family_t ;
typedef  TYPE_2__* ifnet_t ;
typedef  int errno_t ;
struct TYPE_8__ {int if_flags; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int IFF_RUNNING ; 
 int /*<<< orphan*/  IFF_UP ; 
#define  SIOCGIFADDR 129 
#define  SIOCSIFADDR 128 
 int /*<<< orphan*/  SIOCSIFFLAGS ; 
 int /*<<< orphan*/  ifnet_guarded_lladdr_copy_bytes (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_ioctl (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifnet_set_flags (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static errno_t
ether_inet6_prmod_ioctl(ifnet_t ifp, protocol_family_t protocol_family,
    u_long command, void *data)
{
#pragma unused(protocol_family)
	int error = 0;

	switch (command) {
	case SIOCSIFADDR:		/* struct ifaddr pointer */
		/*
		 * Note: caller of ifnet_ioctl() passes in pointer to
		 * struct ifaddr as parameter to SIOCSIFADDR, for legacy
		 * reasons.
		 */
		if ((ifp->if_flags & IFF_RUNNING) == 0) {
			ifnet_set_flags(ifp, IFF_UP, IFF_UP);
			ifnet_ioctl(ifp, 0, SIOCSIFFLAGS, NULL);
		}
		break;

	case SIOCGIFADDR: {		/* struct ifreq */
		struct ifreq *ifr = (struct ifreq *)(void *)data;
		(void) ifnet_guarded_lladdr_copy_bytes(ifp,
		    ifr->ifr_addr.sa_data, ETHER_ADDR_LEN);
		break;
	}

	default:
		error = EOPNOTSUPP;
		break;
	}
	return (error);
}