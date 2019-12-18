#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_4__ {int /*<<< orphan*/  GatewayIP; scalar_t__ LocalRouting; } ;
typedef  TYPE_1__ ROUTE_ENTRY ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 TYPE_1__* GetBestRouteEntry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLocalHostIP4 (int /*<<< orphan*/ *) ; 
 int IsIP4 (int /*<<< orphan*/ *) ; 
 scalar_t__ IsLocalHostIP4 (int /*<<< orphan*/ *) ; 
 scalar_t__ IsZeroIp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ZeroIP4 (int /*<<< orphan*/ *) ; 

bool GetBestLocalIpForTarget(IP *local_ip, IP *target_ip)
{
	bool ret = false;
	ROUTE_ENTRY *e;
	IP ip2;
	UINT n = 0;
	IP zero_ip;
	// Validate arguments
	Zero(local_ip, sizeof(IP));
	ZeroIP4(&zero_ip);
	if (target_ip == NULL)
	{
		target_ip = &zero_ip;
	}
	if (local_ip == NULL || IsIP4(target_ip) == false)
	{
		return false;
	}

	Copy(&ip2, target_ip, sizeof(IP));

	while (true)
	{
		n++;
		if (n >= 64)
		{
			break;
		}

		e = GetBestRouteEntry(&ip2);
		if (e != NULL)
		{
			if (IsZeroIp(&e->GatewayIP))
			{
				Free(e);
				break;
			}

			if (e->LocalRouting)
			{
				ret = true;
				Copy(local_ip, &e->GatewayIP, sizeof(IP));
				Free(e);
				break;
			}
			else
			{
				Copy(&ip2, &e->GatewayIP, sizeof(IP));
			}

			Free(e);
		}
	}

	if (ret == false)
	{
		if (IsLocalHostIP4(target_ip))
		{
			GetLocalHostIP4(local_ip);
			ret = true;
		}
	}

	return ret;
}