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
typedef  int UINT ;
struct TYPE_5__ {int* addr; } ;
typedef  TYPE_1__ IP ;

/* Variables and functions */
 int IsIP4 (TYPE_1__*) ; 
 scalar_t__ IsZeroIP (TYPE_1__*) ; 

bool IsValidUnicastIPAddress4(IP *ip)
{
	UINT i;
	// Validate arguments
	if (IsIP4(ip) == false)
	{
		return false;
	}

	if (IsZeroIP(ip))
	{
		return false;
	}

	if (ip->addr[0] >= 224 && ip->addr[0] <= 239)
	{
		// IPv4 Multicast
		return false;
	}

	for (i = 0;i < 4;i++)
	{
		if (ip->addr[i] != 255)
		{
			return true;
		}
	}

	return false;
}