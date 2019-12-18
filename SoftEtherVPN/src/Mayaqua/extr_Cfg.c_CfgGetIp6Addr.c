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
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int CfgGetIp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int IPToIPv6Addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IsIP6 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

bool CfgGetIp6Addr(FOLDER *f, char *name, IPV6_ADDR *addr)
{
	IP ip;
	// Validate arguments
	Zero(addr, sizeof(IPV6_ADDR));
	if (f == NULL || name == NULL || addr == NULL)
	{
		return false;
	}

	if (CfgGetIp(f, name, &ip) == false)
	{
		return false;
	}

	if (IsIP6(&ip) == false)
	{
		return false;
	}

	if (IPToIPv6Addr(addr, &ip) == false)
	{
		return false;
	}

	return true;
}