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
typedef  size_t UINT ;
struct TYPE_8__ {size_t MemoryBlocksNum; size_t MemorySize; } ;
struct TYPE_7__ {struct TYPE_7__* Next; TYPE_1__* Object; } ;
struct TYPE_6__ {size_t Size; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ TRACKING_OBJECT ;
typedef  TYPE_2__ TRACKING_LIST ;
typedef  TYPE_3__ MEMORY_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  LockTrackingList () ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,char*) ; 
 size_t TRACKING_NUM_ARRAY ; 
 int /*<<< orphan*/  UnlockTrackingList () ; 
 TYPE_2__** hashlist ; 

void GetMemoryStatus(MEMORY_STATUS *status)
{
	UINT i, num, size;
	// Validate arguments
	if (status == NULL)
	{
		return;
	}

	LockTrackingList();
	{
		size = num = 0;

		for (i = 0;i < TRACKING_NUM_ARRAY;i++)
		{
			if (hashlist[i] != NULL)
			{
				TRACKING_LIST *t = hashlist[i];

				while (true)
				{
					TRACKING_OBJECT *o = t->Object;

					if (StrCmpi(o->Name, "MEM") == 0)
					{
						num++;
						size += o->Size;
					}

					if (t->Next == NULL)
					{
						break;
					}

					t = t->Next;
				}
			}
		}
	}
	UnlockTrackingList();

	status->MemoryBlocksNum = num;
	status->MemorySize = size;
}