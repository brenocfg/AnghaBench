#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ServerAddress; } ;
struct TYPE_6__ {int Halt; int /*<<< orphan*/  Cedar; int /*<<< orphan*/  Sock2; int /*<<< orphan*/  Sock1; int /*<<< orphan*/  Cancel; int /*<<< orphan*/ * Ipc; int /*<<< orphan*/  Eth; int /*<<< orphan*/  MainThread; TYPE_3__ CurrentDhcpOptionList; } ;
typedef  TYPE_1__ NATIVE_STACK ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  Cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloseEth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeIPC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  IPCDhcpFreeIP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IsZero (TYPE_3__*,int) ; 
 int /*<<< orphan*/  NsStopIpTablesTracking (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseCancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseCedar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SleepThread (int) ; 
 int /*<<< orphan*/  UINTToIP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void FreeNativeStack(NATIVE_STACK *a)
{
	// Validate arguments
	if (a == NULL)
	{
		return;
	}

	if (a->Ipc != NULL && IsZero(&a->CurrentDhcpOptionList, sizeof(a->CurrentDhcpOptionList)) == false)
	{
		IP dhcp_server;

		UINTToIP(&dhcp_server, a->CurrentDhcpOptionList.ServerAddress);

		IPCDhcpFreeIP(a->Ipc, &dhcp_server);
		SleepThread(200);
	}

	a->Halt = true;
	Cancel(a->Cancel);
	Disconnect(a->Sock1);
	Disconnect(a->Sock2);

	WaitThread(a->MainThread, INFINITE);

	ReleaseThread(a->MainThread);

	CloseEth(a->Eth);
	FreeIPC(a->Ipc);

	NsStopIpTablesTracking(a);

	ReleaseCancel(a->Cancel);

	ReleaseSock(a->Sock1);
	ReleaseSock(a->Sock2);

	ReleaseCedar(a->Cedar);

	Free(a);
}