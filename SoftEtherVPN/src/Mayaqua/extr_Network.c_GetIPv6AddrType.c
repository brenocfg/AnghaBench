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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  IPV6_ADDR ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  GetIPAddrType6 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPv6AddrToIP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

UINT GetIPv6AddrType(IPV6_ADDR *addr)
{
	IP ip;
	// Validate arguments
	if (addr == NULL)
	{
		return 0;
	}

	IPv6AddrToIP(&ip, addr);

	return GetIPAddrType6(&ip);
}