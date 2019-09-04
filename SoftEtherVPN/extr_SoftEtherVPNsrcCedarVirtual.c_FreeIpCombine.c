#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  CurrentIpQuota; } ;
typedef  TYPE_1__ VH ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int /*<<< orphan*/  IpParts; struct TYPE_9__* HeadIpHeaderData; struct TYPE_9__* Data; scalar_t__ DataReserved; } ;
typedef  TYPE_2__ IP_PART ;
typedef  TYPE_2__ IP_COMBINE ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 

void FreeIpCombine(VH *v, IP_COMBINE *c)
{
	UINT i;
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	// Release the data
	v->CurrentIpQuota -= c->DataReserved;
	Free(c->Data);

	// Release the partial list
	for (i = 0;i < LIST_NUM(c->IpParts);i++)
	{
		IP_PART *p = LIST_DATA(c->IpParts, i);

		Free(p);
	}

	Free(c->HeadIpHeaderData);

	ReleaseList(c->IpParts);
	Free(c);
}