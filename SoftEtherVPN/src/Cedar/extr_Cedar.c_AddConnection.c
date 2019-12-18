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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_7__ {int /*<<< orphan*/  ConnectionList; int /*<<< orphan*/  ConnectionIncrement; } ;
struct TYPE_6__ {int /*<<< orphan*/  Name; int /*<<< orphan*/  ref; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ CONNECTION ;
typedef  TYPE_2__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CopyStr (char*) ; 
 int /*<<< orphan*/  Debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Format (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void AddConnection(CEDAR *cedar, CONNECTION *c)
{
	char tmp[MAX_SIZE];
	UINT i;
	// Validate arguments
	if (cedar == NULL || c == NULL)
	{
		return;
	}

	// Determine the name of the connection
	i = Inc(cedar->ConnectionIncrement);
	Format(tmp, sizeof(tmp), "CID-%u", i);


	Lock(c->lock);
	{
		Free(c->Name);
		c->Name = CopyStr(tmp);
	}
	Unlock(c->lock);

	LockList(cedar->ConnectionList);
	{
		Add(cedar->ConnectionList, c);
		AddRef(c->ref);
		Debug("Connection %s Inserted to Cedar.\n", c->Name);
	}
	UnlockList(cedar->ConnectionList);
}