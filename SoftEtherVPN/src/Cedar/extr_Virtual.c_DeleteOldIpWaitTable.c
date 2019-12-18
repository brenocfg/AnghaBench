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
struct TYPE_8__ {scalar_t__ Now; int /*<<< orphan*/ * IpWaitTable; } ;
typedef  TYPE_1__ VH ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {scalar_t__ Expire; struct TYPE_9__* Data; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_2__ IP_WAIT ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 

void DeleteOldIpWaitTable(VH *v)
{
	UINT i;
	LIST *o = NULL;
	// Validate arguments
	if (v == NULL)
	{
		return;
	}

	// Get the deleting list
	for (i = 0;i < LIST_NUM(v->IpWaitTable);i++)
	{
		IP_WAIT *w = LIST_DATA(v->IpWaitTable, i);

		if (w->Expire < v->Now)
		{
			if (o == NULL)
			{
				o = NewListFast(NULL);
			}
			Add(o, w);
		}
	}

	// Delete all at once
	if (o != NULL)
	{
		for (i = 0;i < LIST_NUM(o);i++)
		{
			IP_WAIT *w = LIST_DATA(o, i);

			// Remove from the list
			Delete(v->IpWaitTable, w);

			// Release the memory
			Free(w->Data);
			Free(w);
		}
		ReleaseList(o);
	}
}