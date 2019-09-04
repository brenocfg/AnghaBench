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
struct TYPE_8__ {int /*<<< orphan*/  ConnectionList; } ;
struct TYPE_7__ {int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ CONNECTION ;
typedef  TYPE_2__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ Delete (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseConnection (TYPE_1__*) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void DelConnection(CEDAR *cedar, CONNECTION *c)
{
	// Validate arguments
	if (cedar == NULL || c == NULL)
	{
		return;
	}

	LockList(cedar->ConnectionList);
	{
		Debug("Connection %s Deleted from Cedar.\n", c->Name);
		if (Delete(cedar->ConnectionList, c))
		{
			ReleaseConnection(c);
		}
	}
	UnlockList(cedar->ConnectionList);
}