#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ NetworkAddress; scalar_t__ SubnetMask; scalar_t__ GatewayAddress; scalar_t__ Metric; } ;
typedef  TYPE_1__ L3TABLE ;

/* Variables and functions */

int CmpL3Table(void *p1, void *p2)
{
	L3TABLE *t1, *t2;
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	t1 = *(L3TABLE **)p1;
	t2 = *(L3TABLE **)p2;
	if (t1 == NULL || t2 == NULL)
	{
		return 0;
	}

	if (t1->NetworkAddress > t2->NetworkAddress)
	{
		return 1;
	}
	else if (t1->NetworkAddress < t2->NetworkAddress)
	{
		return -1;
	}
	else if (t1->SubnetMask > t2->SubnetMask)
	{
		return 1;
	}
	else if (t1->SubnetMask < t2->SubnetMask)
	{
		return -1;
	}
	else if (t1->GatewayAddress > t2->GatewayAddress)
	{
		return 1;
	}
	else if (t1->GatewayAddress < t2->GatewayAddress)
	{
		return -1;
	}
	else if (t1->Metric > t2->Metric)
	{
		return 1;
	}
	else if (t1->Metric < t2->Metric)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}