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
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  IPV6_ADDR ;

/* Variables and functions */
 int PackGetDataEx2 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

bool PackGetIp6AddrEx(PACK *p, char *name, IPV6_ADDR *addr, UINT index)
{
	// Validate arguments
	if (p == NULL || name == NULL || addr == NULL)
	{
		Zero(addr, sizeof(IPV6_ADDR));
		return false;
	}

	return PackGetDataEx2(p, name, addr, sizeof(IPV6_ADDR), index);
}