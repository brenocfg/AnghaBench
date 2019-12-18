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
typedef  int UINT ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  FreeHostIPAddressList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetHostIPAddressList () ; 
 int GetIPAddrType6 (int /*<<< orphan*/ *) ; 
 int IPV6_ADDR_GLOBAL_UNICAST ; 
 int IPV6_ADDR_LOCAL_UNICAST ; 
 int /*<<< orphan*/  IntToSubnetMask6 (int /*<<< orphan*/ *,int) ; 
 int IsIP6 (int /*<<< orphan*/ *) ; 
 scalar_t__ IsInSameNetwork6 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IsLocalHostIP6 (int /*<<< orphan*/ *) ; 
 int IsZeroIp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ *,int) ; 
 int LIST_NUM (int /*<<< orphan*/ *) ; 

bool IsIPv6LocalNetworkAddress(IP *ip)
{
	UINT type;
	LIST *o;
	UINT i;
	bool ret = false;
	IP mask64;
	// Validate arguments
	if (ip == NULL)
	{
		return false;
	}
	if (IsIP6(ip) == false)
	{
		return false;
	}
	if (IsZeroIp(ip))
	{
		return false;
	}

	type = GetIPAddrType6(ip);

	if (type & IPV6_ADDR_LOCAL_UNICAST)
	{
		return true;
	}

	if ((type & IPV6_ADDR_GLOBAL_UNICAST) == 0)
	{
		return false;
	}

	IntToSubnetMask6(&mask64, 64);

	o = GetHostIPAddressList();

	ret = false;

	for (i = 0;i < LIST_NUM(o);i++)
	{
		IP *p = LIST_DATA(o, i);

		if (IsIP6(p))
		{
			if (IsZeroIp(p) == false)
			{
				if (IsLocalHostIP6(p) == false)
				{
					if (IsInSameNetwork6(p, ip, &mask64))
					{
						ret = true;
					}
				}
			}
		}
	}

	FreeHostIPAddressList(o);

	return ret;
}