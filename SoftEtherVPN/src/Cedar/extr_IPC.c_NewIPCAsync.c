#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  ref; } ;
struct TYPE_10__ {int /*<<< orphan*/  Thread; TYPE_1__* SockEvent; int /*<<< orphan*/  Param; TYPE_3__* Cedar; int /*<<< orphan*/  TubeForDisconnect; } ;
struct TYPE_9__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ SOCK_EVENT ;
typedef  int /*<<< orphan*/  IPC_PARAM ;
typedef  TYPE_2__ IPC_ASYNC ;
typedef  TYPE_3__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IPCAsyncThreadProc ; 
 int /*<<< orphan*/  NewThread (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  NewTube (int /*<<< orphan*/ ) ; 
 TYPE_2__* ZeroMalloc (int) ; 

IPC_ASYNC *NewIPCAsync(CEDAR *cedar, IPC_PARAM *param, SOCK_EVENT *sock_event)
{
	IPC_ASYNC *a;
	// Validate arguments
	if (cedar == NULL || param == NULL)
	{
		return NULL;
	}

	a = ZeroMalloc(sizeof(IPC_ASYNC));

	a->TubeForDisconnect = NewTube(0);

	a->Cedar = cedar;
	AddRef(a->Cedar->ref);

	Copy(&a->Param, param, sizeof(IPC_PARAM));

	if (sock_event != NULL)
	{
		a->SockEvent = sock_event;
		AddRef(a->SockEvent->ref);
	}

	a->Thread = NewThread(IPCAsyncThreadProc, a);

	return a;
}