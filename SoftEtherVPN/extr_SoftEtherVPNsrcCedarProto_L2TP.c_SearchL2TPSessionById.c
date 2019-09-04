#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int /*<<< orphan*/  TunnelList; } ;
struct TYPE_7__ {scalar_t__ SessionId2; int /*<<< orphan*/  IsV3; } ;
struct TYPE_6__ {int /*<<< orphan*/  SessionList; } ;
typedef  TYPE_1__ L2TP_TUNNEL ;
typedef  TYPE_2__ L2TP_SESSION ;
typedef  TYPE_3__ L2TP_SERVER ;

/* Variables and functions */
 scalar_t__ EQUAL_BOOL (int /*<<< orphan*/ ,int) ; 
 void* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 

L2TP_SESSION *SearchL2TPSessionById(L2TP_SERVER *l2tp, bool is_v3, UINT id)
{
	UINT i, j;
	// Validate arguments
	if (l2tp == NULL || id == 0)
	{
		return NULL;
	}

	for (i = 0;i < LIST_NUM(l2tp->TunnelList);i++)
	{
		L2TP_TUNNEL *t = LIST_DATA(l2tp->TunnelList, i);

		for (j = 0;j < LIST_NUM(t->SessionList);j++)
		{
			L2TP_SESSION *s = LIST_DATA(t->SessionList, j);

			if (s->SessionId2 == id)
			{
				if (EQUAL_BOOL(s->IsV3, is_v3))
				{
					return s;
				}
			}
		}
	}

	return NULL;
}