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
typedef  int /*<<< orphan*/  ITEM ;
typedef  int /*<<< orphan*/  IPV6_ADDR ;
typedef  int /*<<< orphan*/  IP ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/ * CfgAddIp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPv6AddrToIP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

ITEM *CfgAddIp6Addr(FOLDER *f, char *name, IPV6_ADDR *addr)
{
	IP ip;
	// Validate arguments
	if (f == NULL || name == NULL || addr == NULL)
	{
		return NULL;
	}

	IPv6AddrToIP(&ip, addr);

	return CfgAddIp(f, name, &ip);
}