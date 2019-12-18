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
struct TYPE_3__ {int* addr; } ;
typedef  TYPE_1__ IP ;

/* Variables and functions */

bool IsHubIpAddress(IP *ip)
{
	// Validate arguments
	if (ip == NULL)
	{
		return false;
	}

	if (ip->addr[0] == 172 && ip->addr[1] == 31)
	{
		if (ip->addr[2] >= 1 && ip->addr[2] <= 254)
		{
			if (ip->addr[3] >= 1 && ip->addr[3] <= 254)
			{
				return true;
			}
		}
	}

	return false;
}