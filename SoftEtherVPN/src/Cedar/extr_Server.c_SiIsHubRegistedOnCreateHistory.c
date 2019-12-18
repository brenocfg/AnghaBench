#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_7__ {int /*<<< orphan*/  HubCreateHistoryList; } ;
struct TYPE_6__ {int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ SERVER_HUB_CREATE_HISTORY ;
typedef  TYPE_2__ SERVER ;

/* Variables and functions */
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiDeleteOldHubCreateHistory (TYPE_2__*) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

bool SiIsHubRegistedOnCreateHistory(SERVER *s, char *name)
{
	UINT i;
	bool ret = false;
	// Validate arguments
	if (s == NULL || name == NULL)
	{
		return false;
	}

	SiDeleteOldHubCreateHistory(s);

	LockList(s->HubCreateHistoryList);
	{
		for (i = 0;i < LIST_NUM(s->HubCreateHistoryList);i++)
		{
			SERVER_HUB_CREATE_HISTORY *h = LIST_DATA(s->HubCreateHistoryList, i);

			if (StrCmpi(h->HubName, name) == 0)
			{
				ret = true;
				break;
			}
		}
	}
	UnlockList(s->HubCreateHistoryList);

	return ret;
}