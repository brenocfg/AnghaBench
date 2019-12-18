#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_6__ {struct TYPE_6__* Parse_EapMessage; int /*<<< orphan*/ * AvpList; } ;
typedef  TYPE_1__ RADIUS_PACKET ;
typedef  TYPE_1__ RADIUS_AVP ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 

void FreeRadiusPacket(RADIUS_PACKET *p)
{
	UINT i;
	if (p == NULL)
	{
		return;
	}

	if (p->AvpList != NULL)
	{
		for (i = 0;i < LIST_NUM(p->AvpList);i++)
		{
			RADIUS_AVP *a = LIST_DATA(p->AvpList, i);

			Free(a);
		}

		ReleaseList(p->AvpList);
	}

	Free(p->Parse_EapMessage);

	Free(p);
}