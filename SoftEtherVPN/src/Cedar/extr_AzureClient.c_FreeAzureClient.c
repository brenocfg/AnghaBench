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
struct TYPE_8__ {int Halt; int /*<<< orphan*/  Lock; int /*<<< orphan*/  Event; int /*<<< orphan*/  MainThread; TYPE_1__* CurrentSock; } ;
struct TYPE_7__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ SOCK ;
typedef  TYPE_2__ AZURE_CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Disconnect (TYPE_1__*) ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void FreeAzureClient(AZURE_CLIENT *ac)
{
	SOCK *disconnect_sock = NULL;
	// Validate arguments
	if (ac == NULL)
	{
		return;
	}

	ac->Halt = true;

	Lock(ac->Lock);
	{
		if (ac->CurrentSock != NULL)
		{
			disconnect_sock = ac->CurrentSock;

			AddRef(disconnect_sock->ref);
		}
	}
	Unlock(ac->Lock);

	if (disconnect_sock != NULL)
	{
		Disconnect(disconnect_sock);
		ReleaseSock(disconnect_sock);
	}

	Set(ac->Event);

	// Stop main thread
	WaitThread(ac->MainThread, INFINITE);
	ReleaseThread(ac->MainThread);

	ReleaseEvent(ac->Event);

	DeleteLock(ac->Lock);

	Free(ac);
}