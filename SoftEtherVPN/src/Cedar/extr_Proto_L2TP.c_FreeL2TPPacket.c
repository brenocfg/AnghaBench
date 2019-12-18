#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_4__ {struct TYPE_4__* Data; int /*<<< orphan*/ * AvpList; } ;
typedef  TYPE_1__ L2TP_PACKET ;
typedef  int /*<<< orphan*/  L2TP_AVP ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeL2TPAVP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 

void FreeL2TPPacket(L2TP_PACKET *p)
{
	UINT i;
	// Validate arguments
	if (p == NULL)
	{
		return;
	}

	if (p->AvpList != NULL)
	{
		for (i = 0;i < LIST_NUM(p->AvpList);i++)
		{
			L2TP_AVP *a = LIST_DATA(p->AvpList, i);

			FreeL2TPAVP(a);
		}

		ReleaseList(p->AvpList);
	}

	if (p->Data != NULL)
	{
		Free(p->Data);
	}

	Free(p);
}