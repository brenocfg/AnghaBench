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
struct TYPE_8__ {scalar_t__ Now; int /*<<< orphan*/ * ArpTable; } ;
typedef  TYPE_1__ VH ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {scalar_t__ Expire; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_2__ ARP_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 

void RefreshArpTable(VH *v)
{
	UINT i;
	LIST *o;
	// Validate arguments
	if (v == NULL)
	{
		return;
	}

	o = NewListFast(NULL);
	for (i = 0;i < LIST_NUM(v->ArpTable);i++)
	{
		ARP_ENTRY *e = LIST_DATA(v->ArpTable, i);

		// Check for expired
		if (e->Expire < v->Now)
		{
			// Expired
			Add(o, e);
		}
	}

	// Remove expired entries at once
	for (i = 0;i < LIST_NUM(o);i++)
	{
		ARP_ENTRY *e = LIST_DATA(o, i);

		Delete(v->ArpTable, e);
		Free(e);
	}

	ReleaseList(o);
}