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
struct TYPE_8__ {int /*<<< orphan*/  SessionList; int /*<<< orphan*/  Name; } ;
struct TYPE_7__ {int /*<<< orphan*/  UniqueId; scalar_t__ InProcMode; int /*<<< orphan*/  Name; int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ SESSION ;
typedef  TYPE_2__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetNewUniqueId (TYPE_2__*) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void AddSession(HUB *h, SESSION *s)
{
	// Validate arguments
	if (h == NULL || s == NULL)
	{
		return;
	}

	LockList(h->SessionList);
	{
		Insert(h->SessionList, s);
		AddRef(s->ref);
		Debug("Session %s Inserted to %s.\n", s->Name, h->Name);

		if (s->InProcMode)
		{
			s->UniqueId = GetNewUniqueId(h);
		}
	}
	UnlockList(h->SessionList);
}