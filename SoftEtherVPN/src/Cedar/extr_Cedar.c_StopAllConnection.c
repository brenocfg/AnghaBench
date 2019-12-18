#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_3__ {int /*<<< orphan*/  ConnectionList; } ;
typedef  int /*<<< orphan*/  CONNECTION ;
typedef  TYPE_1__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteAll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ **) ; 
 size_t LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseConnection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StopConnection (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ ** ToArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void StopAllConnection(CEDAR *c)
{
	UINT num;
	UINT i;
	CONNECTION **connections;
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	LockList(c->ConnectionList);
	{
		connections = ToArray(c->ConnectionList);
		num = LIST_NUM(c->ConnectionList);
		DeleteAll(c->ConnectionList);
	}
	UnlockList(c->ConnectionList);

	for (i = 0;i < num;i++)
	{
		StopConnection(connections[i], false);
		ReleaseConnection(connections[i]);
	}
	Free(connections);
}