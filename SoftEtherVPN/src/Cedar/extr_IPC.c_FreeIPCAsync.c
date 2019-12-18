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
struct TYPE_4__ {int /*<<< orphan*/  TubeForDisconnect; int /*<<< orphan*/  Cedar; int /*<<< orphan*/ * SockEvent; int /*<<< orphan*/ * Ipc; int /*<<< orphan*/  Thread; } ;
typedef  TYPE_1__ IPC_ASYNC ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeIPC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  ReleaseCedar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSockEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseTube (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TubeDisconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void FreeIPCAsync(IPC_ASYNC *a)
{
	// Validate arguments
	if (a == NULL)
	{
		return;
	}

	TubeDisconnect(a->TubeForDisconnect);
	WaitThread(a->Thread, INFINITE);
	ReleaseThread(a->Thread);

	if (a->Ipc != NULL)
	{
		FreeIPC(a->Ipc);
		a->Ipc = NULL;
	}

	if (a->SockEvent != NULL)
	{
		ReleaseSockEvent(a->SockEvent);
	}

	ReleaseCedar(a->Cedar);

	ReleaseTube(a->TubeForDisconnect);
	Free(a);
}