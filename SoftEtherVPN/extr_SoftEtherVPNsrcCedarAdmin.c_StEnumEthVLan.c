#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {TYPE_1__* Server; } ;
struct TYPE_4__ {int /*<<< orphan*/ * Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  int /*<<< orphan*/  RPC_ENUM_ETH_VLAN ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_2__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  SERVER_ADMIN_ONLY ; 

UINT StEnumEthVLan(ADMIN *a, RPC_ENUM_ETH_VLAN *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	UINT ret = ERR_NO_ERROR;

	SERVER_ADMIN_ONLY;

#ifdef	OS_WIN32
	if (GetServerCapsBool(s, "b_support_eth_vlan") == false)
	{
		ret = ERR_NOT_SUPPORTED;
	}
	else
	{
		FreeRpcEnumEthVLan(t);
		Zero(t, sizeof(RPC_ENUM_ETH_VLAN));

		if (EnumEthVLanWin32(t) == false)
		{
			ret = ERR_INTERNAL_ERROR;
		}
	}
#else	// OS_WIN32
	ret = ERR_NOT_SUPPORTED;
#endif	// OS_WIN32

	return ret;
}