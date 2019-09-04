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
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTTY ; 
 int /*<<< orphan*/  IFF_RUNNING ; 
 int IFF_UP ; 
#define  SIOCAIFADDR 131 
#define  SIOCSIFADDR 130 
#define  SIOCSIFDSTADDR 129 
#define  SIOCSIFFLAGS 128 
 int ifnet_flags (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_set_flags (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static errno_t
pflogioctl(struct ifnet *ifp, unsigned long cmd, void *data)
{
#pragma unused(data)
	switch (cmd) {
	case SIOCSIFADDR:
	case SIOCAIFADDR:
	case SIOCSIFDSTADDR:
	case SIOCSIFFLAGS:
		if (ifnet_flags(ifp) & IFF_UP)
			ifnet_set_flags(ifp, IFF_RUNNING, IFF_RUNNING);
		else
			ifnet_set_flags(ifp, 0, IFF_RUNNING);
		break;
	default:
		return (ENOTTY);
	}

	return (0);
}