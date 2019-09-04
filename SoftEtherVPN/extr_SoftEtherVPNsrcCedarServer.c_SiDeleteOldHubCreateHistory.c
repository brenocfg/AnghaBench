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
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int /*<<< orphan*/ * HubCreateHistoryList; } ;
struct TYPE_8__ {scalar_t__ CreatedTime; } ;
typedef  TYPE_1__ SERVER_HUB_CREATE_HISTORY ;
typedef  TYPE_2__ SERVER ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 scalar_t__ TICKET_EXPIRES ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ *) ; 

void SiDeleteOldHubCreateHistory(SERVER *s)
{
	UINT i;
	LIST *o;
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	LockList(s->HubCreateHistoryList);
	{
		o = NewListFast(NULL);

		for (i = 0;i < LIST_NUM(s->HubCreateHistoryList);i++)
		{
			SERVER_HUB_CREATE_HISTORY *h = LIST_DATA(s->HubCreateHistoryList, i);

			if ((h->CreatedTime + ((UINT64)TICKET_EXPIRES)) <= Tick64())
			{
				// Expired
				Add(o, h);
			}
		}

		for (i = 0;i < LIST_NUM(o);i++)
		{
			SERVER_HUB_CREATE_HISTORY *h = LIST_DATA(o, i);

			Delete(s->HubCreateHistoryList, h);

			Free(h);
		}

		ReleaseList(o);
	}
	UnlockList(s->HubCreateHistoryList);
}