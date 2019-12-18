#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_3__ {scalar_t__ Mask; scalar_t__ Ip2; } ;
typedef  TYPE_1__ PRIVATE_IP_SUBNET ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_private_ip_list ; 

bool IsOnPrivateIPFile(UINT ip)
{
	bool ret = false;

	if (g_private_ip_list != NULL)
	{
		LIST *o = g_private_ip_list;
		UINT i;

		for (i = 0;i < LIST_NUM(o);i++)
		{
			PRIVATE_IP_SUBNET *p = LIST_DATA(o, i);

			if ((ip & p->Mask) == p->Ip2)
			{
				ret = true;
			}
		}
	}

	return ret;
}