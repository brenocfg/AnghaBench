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
typedef  int /*<<< orphan*/  IPV6_ADDR ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int IPToIPv6Addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int StrToIP6 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

bool StrToIP6Addr(IPV6_ADDR *ip, char *str)
{
	IP ip2;
	// Validate arguments
	if (ip == NULL || str == NULL)
	{
		Zero(ip, sizeof(IPV6_ADDR));
		return false;
	}

	if (StrToIP6(&ip2, str) == false)
	{
		return false;
	}

	if (IPToIPv6Addr(ip, &ip2) == false)
	{
		return false;
	}

	return true;
}