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
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IFNET_IS_EXPENSIVE (struct ifnet*) ; 
#define  IFRTYPE_FUNCTIONAL_CELLULAR 134 
#define  IFRTYPE_FUNCTIONAL_INTCOPROC 133 
 int IFRTYPE_FUNCTIONAL_LAST ; 
#define  IFRTYPE_FUNCTIONAL_LOOPBACK 132 
#define  IFRTYPE_FUNCTIONAL_UNKNOWN 131 
#define  IFRTYPE_FUNCTIONAL_WIFI_AWDL 130 
#define  IFRTYPE_FUNCTIONAL_WIFI_INFRA 129 
#define  IFRTYPE_FUNCTIONAL_WIRED 128 
 int /*<<< orphan*/  NSTAT_IFNET_IS_AWDL ; 
 int /*<<< orphan*/  NSTAT_IFNET_IS_CELLULAR ; 
 int /*<<< orphan*/  NSTAT_IFNET_IS_EXPENSIVE ; 
 int /*<<< orphan*/  NSTAT_IFNET_IS_LOOPBACK ; 
 int /*<<< orphan*/  NSTAT_IFNET_IS_UNKNOWN_TYPE ; 
 int /*<<< orphan*/  NSTAT_IFNET_IS_WIFI ; 
 int /*<<< orphan*/  NSTAT_IFNET_IS_WIRED ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int if_functional_type (struct ifnet*,int /*<<< orphan*/ ) ; 

u_int16_t
nstat_ifnet_to_flags(
	struct ifnet *ifp)
{
	u_int16_t flags = 0;
	u_int32_t functional_type = if_functional_type(ifp, FALSE);

	/* Panic if someone adds a functional type without updating ntstat. */
	VERIFY(0 <= functional_type && functional_type <= IFRTYPE_FUNCTIONAL_LAST);

	switch (functional_type)
	{
	case IFRTYPE_FUNCTIONAL_UNKNOWN:
		flags |= NSTAT_IFNET_IS_UNKNOWN_TYPE;
		break;
	case IFRTYPE_FUNCTIONAL_LOOPBACK:
		flags |= NSTAT_IFNET_IS_LOOPBACK;
		break;
	case IFRTYPE_FUNCTIONAL_WIRED:
	case IFRTYPE_FUNCTIONAL_INTCOPROC:
		flags |= NSTAT_IFNET_IS_WIRED;
		break;
	case IFRTYPE_FUNCTIONAL_WIFI_INFRA:
		flags |= NSTAT_IFNET_IS_WIFI;
		break;
	case IFRTYPE_FUNCTIONAL_WIFI_AWDL:
		flags |= NSTAT_IFNET_IS_WIFI;
		flags |= NSTAT_IFNET_IS_AWDL;
		break;
	case IFRTYPE_FUNCTIONAL_CELLULAR:
		flags |= NSTAT_IFNET_IS_CELLULAR;
		break;
	}

	if (IFNET_IS_EXPENSIVE(ifp))
	{
		flags |= NSTAT_IFNET_IS_EXPENSIVE;
	}

	return flags;
}