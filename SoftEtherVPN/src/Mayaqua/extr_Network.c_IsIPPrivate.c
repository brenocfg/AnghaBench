#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {int* addr; } ;
typedef  TYPE_1__ IP ;

/* Variables and functions */
 int /*<<< orphan*/  IPToUINT (TYPE_1__*) ; 
 scalar_t__ IsIP4 (TYPE_1__*) ; 
 int IsOnPrivateIPFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_private_ip_list ; 

bool IsIPPrivate(IP *ip)
{
	// Validate arguments
	if (ip == NULL)
	{
		return false;
	}

	if (ip->addr[0] == 10)
	{
		return true;
	}

	if (ip->addr[0] == 172)
	{
		if (ip->addr[1] >= 16 && ip->addr[1] <= 31)
		{
			return true;
		}
	}

	if (ip->addr[0] == 192 && ip->addr[1] == 168)
	{
		return true;
	}

	if (ip->addr[0] == 169 && ip->addr[1] == 254)
	{
		return true;
	}

	if (ip->addr[0] == 100)
	{
		if (ip->addr[1] >= 64 && ip->addr[1] <= 127)
		{
			return true;
		}
	}

	if (g_private_ip_list != NULL)
	{
		if (IsIP4(ip))
		{
			UINT ip4 = IPToUINT(ip);

			return IsOnPrivateIPFile(ip4);
		}
	}

	return false;
}