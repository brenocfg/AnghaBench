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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 scalar_t__ CmpIpAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeHostIPAddressList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetHostIPAddressList () ; 
 scalar_t__ IsLocalHostIP (int /*<<< orphan*/ *) ; 
 scalar_t__ IsZeroIp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 

bool IsIPMyHost(IP *ip)
{
	LIST *o;
	UINT i;
	bool ret = false;
	// Validate arguments
	if (ip == NULL)
	{
		return false;
	}

	if (IsZeroIp(ip))
	{
		return false;
	}

	// Search to check whether it matches to any of the IP of the local host
	o = GetHostIPAddressList();

	for (i = 0;i < LIST_NUM(o);i++)
	{
		IP *p = LIST_DATA(o, i);

		if (CmpIpAddr(p, ip) == 0)
		{
			// Matched
			ret = true;
			break;
		}
	}

	FreeHostIPAddressList(o);

	if (ret == false)
	{
		if (IsLocalHostIP(ip))
		{
			// localhost IP addresses
			ret = true;
		}
	}

	return ret;
}