#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int IpTablesInitOk; int IpTablesHalt; int /*<<< orphan*/ * IpTablesThread; int /*<<< orphan*/  IpTablesHaltEvent; } ;
typedef  TYPE_1__ NATIVE_STACK ;

/* Variables and functions */
 int /*<<< orphan*/  NewEvent () ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  NsIpTablesThread ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ *) ; 

bool NsStartIpTablesTracking(NATIVE_STACK *a)
{
	if (a->IpTablesThread != NULL)
	{
		return true;
	}

	a->IpTablesInitOk = false;

	a->IpTablesHalt = false;

	a->IpTablesHaltEvent = NewEvent();

	a->IpTablesThread = NewThread(NsIpTablesThread, a);

	WaitThreadInit(a->IpTablesThread);

	return a->IpTablesInitOk;
}