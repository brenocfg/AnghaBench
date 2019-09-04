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
struct in_addr {int dummy; } ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_4__ {int /*<<< orphan*/ * addr; } ;
typedef  TYPE_1__ IP ;

/* Variables and functions */
 int IsIP6 (TYPE_1__*) ; 
 int /*<<< orphan*/  Zero (struct in_addr*,int) ; 

void IPToInAddr(struct in_addr *addr, IP *ip)
{
	UINT i;
	// Validate arguments
	if (addr == NULL || ip == NULL)
	{
		return;
	}

	Zero(addr, sizeof(struct in_addr));

	if (IsIP6(ip) == false)
	{
		for (i = 0;i < 4;i++)
		{
			((UCHAR *)addr)[i] = ip->addr[i];
		}
	}
}