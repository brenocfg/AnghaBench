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
typedef  scalar_t__ UCHAR ;
struct TYPE_7__ {scalar_t__ Type; } ;
struct TYPE_6__ {int /*<<< orphan*/  AvpList; } ;
typedef  TYPE_1__ RADIUS_PACKET ;
typedef  TYPE_2__ RADIUS_AVP ;

/* Variables and functions */
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 

RADIUS_AVP *GetRadiusAvp(RADIUS_PACKET *p, UCHAR type)
{
	UINT i;
	if (p == NULL)
	{
		return NULL;
	}

	for (i = 0;i < LIST_NUM(p->AvpList);i++)
	{
		RADIUS_AVP *avp = LIST_DATA(p->AvpList, i);

		if (avp->Type == type)
		{
			return avp;
		}
	}

	return NULL;
}