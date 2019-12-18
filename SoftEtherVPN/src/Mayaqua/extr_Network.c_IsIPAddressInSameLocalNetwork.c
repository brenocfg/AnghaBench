#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int* addr; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ IP ;

/* Variables and functions */
 int /*<<< orphan*/  FreeHostIPAddressList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetHostIPAddressList () ; 
 scalar_t__ IsIP4 (TYPE_1__*) ; 
 scalar_t__ IsInSameNetwork4Standard (TYPE_1__*,TYPE_1__*) ; 
 int IsZeroIp (TYPE_1__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 

bool IsIPAddressInSameLocalNetwork(IP *a)
{
	bool ret = false;
	LIST *o;
	UINT i;
	// Validate arguments
	if (a == NULL)
	{
		return false;
	}

	o = GetHostIPAddressList();

	if (o != NULL)
	{
		for (i = 0;i < LIST_NUM(o);i++)
		{
			IP *p = LIST_DATA(o, i);

			if (IsIP4(p))
			{
				if (IsZeroIp(p) == false && p->addr[0] != 127)
				{
					if (IsInSameNetwork4Standard(p, a))
					{
						ret = true;
						break;
					}
				}
			}
		}

		FreeHostIPAddressList(o);
	}

	return ret;
}