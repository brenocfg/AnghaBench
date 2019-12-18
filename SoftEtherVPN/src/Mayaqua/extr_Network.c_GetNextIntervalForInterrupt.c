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
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int /*<<< orphan*/ * TickList; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ INTERRUPT_MANAGER ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  Free (scalar_t__*) ; 
 scalar_t__ INFINITE ; 
 scalar_t__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 int LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ *) ; 

UINT GetNextIntervalForInterrupt(INTERRUPT_MANAGER *m)
{
	UINT ret = INFINITE;
	UINT i;
	LIST *o = NULL;
	UINT64 now = Tick64();
	// Validate arguments
	if (m == NULL)
	{
		return 0;
	}

	LockList(m->TickList);
	{
		// Remove entries older than now already
		for (i = 0;i < LIST_NUM(m->TickList);i++)
		{
			UINT64 *v = LIST_DATA(m->TickList, i);

			if (now >= *v)
			{
				ret = 0;

				if (o == NULL)
				{
					o = NewListFast(NULL);
				}

				Add(o, v);
			}
			else
			{
				break;
			}
		}

		for (i = 0;i < LIST_NUM(o);i++)
		{
			UINT64 *v = LIST_DATA(o, i);

			Free(v);

			Delete(m->TickList, v);
		}

		if (o != NULL)
		{
			ReleaseList(o);
		}

		if (ret == INFINITE)
		{
			if (LIST_NUM(m->TickList) >= 1)
			{
				UINT64 *v = LIST_DATA(m->TickList, 0);

				ret = (UINT)(*v - now);
			}
		}
	}
	UnlockList(m->TickList);

	return ret;
}