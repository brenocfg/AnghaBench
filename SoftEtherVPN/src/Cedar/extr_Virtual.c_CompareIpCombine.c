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
struct TYPE_2__ {scalar_t__ Id; scalar_t__ DestIP; scalar_t__ SrcIP; scalar_t__ Protocol; } ;
typedef  TYPE_1__ IP_COMBINE ;

/* Variables and functions */

int CompareIpCombine(void *p1, void *p2)
{
	IP_COMBINE *c1, *c2;
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	c1 = *(IP_COMBINE **)p1;
	c2 = *(IP_COMBINE **)p2;
	if (c1 == NULL || c2 == NULL)
	{
		return 0;
	}
	if (c1->Id > c2->Id)
	{
		return 1;
	}
	else if (c1->Id < c2->Id)
	{
		return -1;
	}
	else if (c1->DestIP > c2->DestIP)
	{
		return 1;
	}
	else if (c1->DestIP < c2->DestIP)
	{
		return -1;
	}
	else if (c1->SrcIP > c2->SrcIP)
	{
		return 1;
	}
	else if (c1->SrcIP < c2->SrcIP)
	{
		return -1;
	}
	else if (c1->Protocol > c2->Protocol)
	{
		return 1;
	}
	else if (c1->Protocol < c2->Protocol)
	{
		return -1;
	}
	return 0;
}