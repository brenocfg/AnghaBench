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
struct TYPE_3__ {int /*<<< orphan*/  NotifyCancelList; scalar_t__ Halt; } ;
typedef  int /*<<< orphan*/  SOCKSET ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  TYPE_1__ CLIENT ;
typedef  int /*<<< orphan*/  CANCEL ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AddSockSet (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  InitSockSet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewCancel () ; 
 int /*<<< orphan*/  ReleaseCancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Select (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ Send (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void CiNotifyMain(CLIENT *c, SOCK *s)
{
	CANCEL *cancel;
	// Validate arguments
	if (c == NULL || s == NULL)
	{
		return;
	}

	// Register a Cancel
	cancel = NewCancel();
	LockList(c->NotifyCancelList);
	{
		Add(c->NotifyCancelList, cancel);
	}
	UnlockList(c->NotifyCancelList);

	// Wait
	while (true)
	{
		char ch = '@';
		SOCKSET set;
		InitSockSet(&set);
		AddSockSet(&set, s);
		Select(&set, INFINITE, cancel, NULL);

		if (c->Halt)
		{
			// Abort
			break;
		}

		// 1 byte transmission
		if (Send(s, &ch, 1, false) == 0)
		{
			// Disconnected
			break;
		}
	}

	// Disconnect
	Disconnect(s);

	// Unregister the Cancel
	LockList(c->NotifyCancelList);
	{
		Delete(c->NotifyCancelList, cancel);
	}
	UnlockList(c->NotifyCancelList);

	ReleaseCancel(cancel);
}