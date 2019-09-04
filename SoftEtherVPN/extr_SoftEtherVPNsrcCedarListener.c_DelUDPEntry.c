#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_7__ {int /*<<< orphan*/ * Session; } ;
typedef  TYPE_1__ UDP_ENTRY ;
struct TYPE_8__ {int /*<<< orphan*/  UDPEntryList; } ;
typedef  int /*<<< orphan*/  SESSION ;
typedef  TYPE_2__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSession (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void DelUDPEntry(CEDAR *cedar, SESSION *session)
{
	UINT num, i;
	// Validate arguments
	if (cedar == NULL || session == NULL)
	{
		return;
	}

	LockList(cedar->UDPEntryList);
	{
		num = LIST_NUM(cedar->UDPEntryList);
		for (i = 0;i < num;i++)
		{
			UDP_ENTRY *e = LIST_DATA(cedar->UDPEntryList, i);
			if (e->Session == session)
			{
				ReleaseSession(e->Session);
				Delete(cedar->UDPEntryList, e);
				Free(e);
				UnlockList(cedar->UDPEntryList);
				Debug("UDP_Entry Deleted.\n");
				return;
			}
		}
	}
	UnlockList(cedar->UDPEntryList);
}