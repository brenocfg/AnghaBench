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
typedef  size_t UINT ;
struct TYPE_3__ {struct TYPE_3__* Next; int /*<<< orphan*/  Object; } ;
typedef  int /*<<< orphan*/  TRACKING_OBJECT ;
typedef  TYPE_1__ TRACKING_LIST ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ LIST_DATA (int /*<<< orphan*/ *,size_t) ; 
 size_t LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockTrackingList () ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Print (char*) ; 
 int /*<<< orphan*/  PrintObjectList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Sort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SortObjectView ; 
 size_t TRACKING_NUM_ARRAY ; 
 int /*<<< orphan*/  UnlockTrackingList () ; 
 TYPE_1__** hashlist ; 

void DebugPrintAllObjects()
{
	UINT i;
	LIST *view;

	// Creating a List
	view = NewListFast(SortObjectView);
	LockTrackingList();
	{
		for (i = 0;i < TRACKING_NUM_ARRAY;i++)
		{
			if (hashlist[i] != NULL)
			{
				TRACKING_LIST *t = hashlist[i];

				while (true)
				{
					Add(view, t->Object);

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

	// Sort
	Sort(view);

	// Drawing
	for (i = 0;i < LIST_NUM(view);i++)
	{
		TRACKING_OBJECT *o = (TRACKING_OBJECT *)LIST_DATA(view, i);
		PrintObjectList(o);
	}

	// Release the list
	ReleaseList(view);

	Print("\n");
}