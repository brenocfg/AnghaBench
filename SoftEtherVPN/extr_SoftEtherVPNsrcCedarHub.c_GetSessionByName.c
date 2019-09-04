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
struct TYPE_7__ {int /*<<< orphan*/  SessionList; } ;
struct TYPE_6__ {int /*<<< orphan*/  ref; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ SESSION ;
typedef  TYPE_2__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

SESSION *GetSessionByName(HUB *hub, char *name)
{
	// Validate arguments
	if (hub == NULL || name == NULL)
	{
		return NULL;
	}

	LockList(hub->SessionList);
	{
		UINT i;
		for (i = 0;i < LIST_NUM(hub->SessionList);i++)
		{
			SESSION *s = LIST_DATA(hub->SessionList, i);
			if (StrCmpi(s->Name, name) == 0)
			{
				// Found
				AddRef(s->ref);
				UnlockList(hub->SessionList);
				return s;
			}
		}
	}
	UnlockList(hub->SessionList);

	return NULL;
}