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
struct TYPE_4__ {int* ipv6_addr; } ;
typedef  TYPE_1__ IP ;

/* Variables and functions */
 int /*<<< orphan*/  ZeroIP6 (TYPE_1__*) ; 

void GetAllRouterMulticastAddress6(IP *ip)
{
	// Validate arguments
	if (ip == NULL)
	{
		return;
	}

	ZeroIP6(ip);

	ip->ipv6_addr[0] = 0xff;
	ip->ipv6_addr[1] = 0x02;
	ip->ipv6_addr[15] = 0x02;
}