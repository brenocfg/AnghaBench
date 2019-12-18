#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_7__ {int /*<<< orphan*/  TableList; } ;
struct TYPE_6__ {scalar_t__ NetworkAddress; scalar_t__ SubnetMask; scalar_t__ Metric; } ;
typedef  TYPE_1__ L3TABLE ;
typedef  TYPE_2__ L3SW ;

/* Variables and functions */
 scalar_t__ INFINITE ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 

L3TABLE *L3GetBestRoute(L3SW *s, UINT ip)
{
	UINT i;
	UINT max_mask = 0;
	UINT min_metric = INFINITE;
	L3TABLE *ret = NULL;
	// Validate arguments
	if (s == NULL || ip == 0)
	{
		return NULL;
	}

	// 1st condition: Choose the one which have the largest subnet mask
	// 2nd condition: Choose the one which have the smallest metric
	for (i = 0;i < LIST_NUM(s->TableList);i++)
	{
		L3TABLE *t = LIST_DATA(s->TableList, i);

		if ((t->NetworkAddress & t->SubnetMask) == (ip & t->SubnetMask))
		{
			if (t->SubnetMask >= max_mask)
			{
				max_mask = t->SubnetMask;
				if (min_metric >= t->Metric)
				{
					min_metric = t->Metric;
					ret = t;
				}
			}
		}
	}

	return ret;
}