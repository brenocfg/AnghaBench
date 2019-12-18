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
struct TYPE_6__ {scalar_t__ Stopped; } ;
typedef  TYPE_1__ THREAD ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseThread (TYPE_1__*) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ *) ; 

void MaintainThreadList(LIST *o)
{
	UINT i;
	LIST *delete_list = NULL;
	// Validate arguments
	if (o == NULL)
	{
		return;
	}

	LockList(o);
	{
		for (i = 0;i < LIST_NUM(o);i++)
		{
			THREAD *t = LIST_DATA(o, i);

			if (t->Stopped)
			{
				if (delete_list == NULL)
				{
					delete_list = NewListFast(NULL);
				}

				Add(delete_list, t);
			}
		}

		if (delete_list != NULL)
		{
			for (i = 0;i < LIST_NUM(delete_list);i++)
			{
				THREAD *t = LIST_DATA(delete_list, i);

				ReleaseThread(t);

				Delete(o, t);
			}

			ReleaseList(delete_list);
		}
	}
	UnlockList(o);
}