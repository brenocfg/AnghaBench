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
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_6__ {scalar_t__ UpdatedTime; scalar_t__ DhcpAllocated; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ IP_TABLE_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 scalar_t__ IP_TABLE_EXPIRE_TIME ; 
 scalar_t__ IP_TABLE_EXPIRE_TIME_DHCP ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 scalar_t__ Tick64 () ; 

void DeleteExpiredIpTableEntry(LIST *o)
{
	LIST *o2;
	UINT i;
	// Validate arguments
	if (o == NULL)
	{
		return;
	}

	o2 = NewListFast(NULL);

	for (i = 0;i < LIST_NUM(o);i++)
	{
		IP_TABLE_ENTRY *e = LIST_DATA(o, i);
		if ((e->UpdatedTime + (UINT64)(e->DhcpAllocated ? IP_TABLE_EXPIRE_TIME_DHCP : IP_TABLE_EXPIRE_TIME)) <= Tick64())
		{
			Add(o2, e);
		}
	}

	for (i = 0;i < LIST_NUM(o2);i++)
	{
		IP_TABLE_ENTRY *e = LIST_DATA(o2, i);
		Delete(o, e);
		Free(e);
	}

	ReleaseList(o2);
}