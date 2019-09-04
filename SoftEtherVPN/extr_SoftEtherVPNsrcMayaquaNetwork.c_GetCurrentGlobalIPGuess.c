#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_13__ {int* addr; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ IP ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  FreeHostIPAddressList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetHostIPAddressList () ; 
 scalar_t__ GetIPAddrType6 (TYPE_1__*) ; 
 scalar_t__ IPV6_ADDR_GLOBAL_UNICAST ; 
 scalar_t__ IPV6_ADDR_LOOPBACK ; 
 scalar_t__ IPV6_ADDR_ZERO ; 
 scalar_t__ IsIP4 (TYPE_1__*) ; 
 scalar_t__ IsIP6 (TYPE_1__*) ; 
 int IsIPPrivate (TYPE_1__*) ; 
 int IsZeroIp (TYPE_1__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetIP (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void GetCurrentGlobalIPGuess(IP *ip, bool ipv6)
{
	LIST *o;
	UINT i;
	// Validate arguments
	if (ip == NULL)
	{
		return;
	}

	Zero(ip, sizeof(IP));

	o = GetHostIPAddressList();

	if (ipv6 == false)
	{
		// IPv4
		for (i = 0;i < LIST_NUM(o);i++)
		{
			IP *p = LIST_DATA(o, i);

			if (IsIP4(p))
			{
				if (IsZeroIp(p) == false && IsIPPrivate(p) == false && p->addr[0] != 127)
				{
					Copy(ip, p, sizeof(IP));
				}
			}
		}

		if (IsZeroIp(ip))
		{
			for (i = 0;i < LIST_NUM(o);i++)
			{
				IP *p = LIST_DATA(o, i);

				if (IsIP4(p))
				{
					if (IsZeroIp(p) == false && IsIPPrivate(p) && p->addr[0] != 127)
					{
						Copy(ip, p, sizeof(IP));
					}
				}
			}
		}

		if (IsZeroIp(ip))
		{
			SetIP(ip, 127, 0, 0, 1);
		}
	}
	else
	{
		// IPv6
		for (i = 0;i < LIST_NUM(o);i++)
		{
			IP *p = LIST_DATA(o, i);

			if (IsIP6(p))
			{
				UINT type = GetIPAddrType6(p);

				if ((type & IPV6_ADDR_GLOBAL_UNICAST) && ((type & IPV6_ADDR_ZERO) == 0) && ((type & IPV6_ADDR_LOOPBACK) == 0))
				{
					Copy(ip, p, sizeof(IP));
				}
			}
		}
	}

	FreeHostIPAddressList(o);
}