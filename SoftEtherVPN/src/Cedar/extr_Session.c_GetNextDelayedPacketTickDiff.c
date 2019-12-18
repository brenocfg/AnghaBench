#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  int UINT ;
struct TYPE_6__ {scalar_t__ DelayedForwardTick; } ;
struct TYPE_5__ {int /*<<< orphan*/  DelayedPacketList; } ;
typedef  TYPE_1__ SESSION ;
typedef  TYPE_2__ PKT ;

/* Variables and functions */
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,int) ; 
 int LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int MIN (int,int) ; 
 scalar_t__ TickHighres64 () ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

UINT GetNextDelayedPacketTickDiff(SESSION *s)
{
	UINT i;
	UINT ret = 0x7fffffff;
	UINT64 now;
	// Validate arguments
	if (s == NULL)
	{
		return 0;
	}

	if (LIST_NUM(s->DelayedPacketList) >= 1)
	{
		now = TickHighres64();

		LockList(s->DelayedPacketList);
		{
			for (i = 0;i < LIST_NUM(s->DelayedPacketList);i++)
			{
				PKT *p = LIST_DATA(s->DelayedPacketList, i);
				UINT64 t = p->DelayedForwardTick;
				UINT d = 0x7fffffff;

				if (now >= t)
				{
					d = 0;
				}
				else
				{
					d = (UINT)(t - now);
				}

				ret = MIN(ret, d);
			}
		}
		UnlockList(s->DelayedPacketList);
	}

	return ret;
}