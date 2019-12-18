#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
typedef  int sa_family_t ;
typedef  TYPE_1__* ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_3__ {scalar_t__ if_mtu; int if_hwassist; scalar_t__ if_tso_v6_mtu; scalar_t__ if_tso_v4_mtu; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EPROTONOSUPPORT ; 
 int IFNET_TSO_IPV4 ; 
 int IFNET_TSO_IPV6 ; 

errno_t
ifnet_set_tso_mtu(ifnet_t interface, sa_family_t family, u_int32_t mtuLen)
{
	errno_t error = 0;

	if (interface == NULL || mtuLen < interface->if_mtu)
		return (EINVAL);

	switch (family) {
	case AF_INET:
		if (interface->if_hwassist & IFNET_TSO_IPV4)
			interface->if_tso_v4_mtu = mtuLen;
		else
			error = EINVAL;
		break;

	case AF_INET6:
		if (interface->if_hwassist & IFNET_TSO_IPV6)
			interface->if_tso_v6_mtu = mtuLen;
		else
			error = EINVAL;
		break;

	default:
		error = EPROTONOSUPPORT;
		break;
	}

	return (error);
}