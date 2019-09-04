#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_6__ {size_t SubnetMaskLen; int /*<<< orphan*/  SubnetMask; int /*<<< orphan*/  Network; scalar_t__ Exists; } ;
struct TYPE_5__ {scalar_t__ NumExistingRoutes; TYPE_2__* Entries; } ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_1__ DHCP_CLASSLESS_ROUTE_TABLE ;
typedef  TYPE_2__ DHCP_CLASSLESS_ROUTE ;

/* Variables and functions */
 scalar_t__ IsInSameNetwork4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t MAX_DHCP_CLASSLESS_ROUTE_ENTRIES ; 

DHCP_CLASSLESS_ROUTE *GetBestClasslessRoute(DHCP_CLASSLESS_ROUTE_TABLE *t, IP *ip)
{
	DHCP_CLASSLESS_ROUTE *ret = NULL;
	UINT i;
	UINT max_mask = 0;
	// Validate arguments
	if (t == NULL || ip == NULL)
	{
		return NULL;
	}
	if (t->NumExistingRoutes == 0)
	{
		return NULL;
	}

	for (i = 0;i < MAX_DHCP_CLASSLESS_ROUTE_ENTRIES;i++)
	{
		DHCP_CLASSLESS_ROUTE *e = &t->Entries[i];

		if (e->Exists)
		{
			if (IsInSameNetwork4(ip, &e->Network, &e->SubnetMask))
			{
				if (max_mask <= e->SubnetMaskLen)
				{
					max_mask = e->SubnetMaskLen;
					ret = e;
				}
			}
		}
	}

	return ret;
}