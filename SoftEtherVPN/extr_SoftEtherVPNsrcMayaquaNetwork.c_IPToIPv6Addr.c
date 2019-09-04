#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_8__ {int /*<<< orphan*/ * ipv6_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/ * Value; } ;
typedef  TYPE_1__ IPV6_ADDR ;
typedef  TYPE_2__ IP ;

/* Variables and functions */
 int IsIP6 (TYPE_2__*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

bool IPToIPv6Addr(IPV6_ADDR *addr, IP *ip)
{
	UINT i;
	// Validate arguments
	if (addr == NULL || ip == NULL)
	{
		Zero(addr, sizeof(IPV6_ADDR));
		return false;
	}

	if (IsIP6(ip) == false)
	{
		Zero(addr, sizeof(IPV6_ADDR));
		return false;
	}

	for (i = 0;i < 16;i++)
	{
		addr->Value[i] = ip->ipv6_addr[i];
	}

	return true;
}