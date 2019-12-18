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
typedef  scalar_t__ UINT ;
struct TYPE_9__ {scalar_t__ Expire; } ;
struct TYPE_8__ {scalar_t__ LastDeleteOldArpTable; int /*<<< orphan*/ * ArpTable; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ L3IF ;
typedef  TYPE_2__ L3ARPENTRY ;

/* Variables and functions */
 scalar_t__ ARP_ENTRY_POLLING_TIME ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 scalar_t__ Tick64 () ; 

void L3DeleteOldArpTable(L3IF *f)
{
	UINT i;
	LIST *o = NULL;
	// Validate arguments
	if (f == NULL)
	{
		return;
	}

	if ((f->LastDeleteOldArpTable + ARP_ENTRY_POLLING_TIME) > Tick64())
	{
		return;
	}
	f->LastDeleteOldArpTable = Tick64();

	for (i = 0;i < LIST_NUM(f->ArpTable);i++)
	{
		L3ARPENTRY *a = LIST_DATA(f->ArpTable, i);

		if (a->Expire <= Tick64())
		{
			// Expired
			if (o == NULL)
			{
				o = NewListFast(NULL);
			}

			Insert(o, a);
		}
	}

	if (o != NULL)
	{
		for (i = 0;i < LIST_NUM(o);i++)
		{
			L3ARPENTRY *a = LIST_DATA(o, i);

			Delete(f->ArpTable, a);
			Free(a);
		}

		ReleaseList(o);
	}
}