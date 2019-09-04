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
 scalar_t__ IsLocalHostIP4 (int /*<<< orphan*/ *) ; 
 scalar_t__ IsLocalHostIP6 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 

bool IsIPLocalHostOrMySelf(IP *ip)
{
	LIST *o;
	bool ret = false;
	UINT i;
	// Validate arguments
	if (ip == NULL)
	{
		return false;
	}

	o = GetHostIPAddressList();
	if (o == NULL)
	{
		return false;
	}

	for (i = 0;i < LIST_NUM(o);i++)
	{
		IP *p = LIST_DATA(o, i);

		if (CmpIpAddr(p, ip) == 0)
		{
			ret = true;

			break;
		}
	}

	FreeHostIPAddressList(o);

	if (IsLocalHostIP4(ip) || IsLocalHostIP6(ip))
	{
		ret = true;
	}

	return ret;
}