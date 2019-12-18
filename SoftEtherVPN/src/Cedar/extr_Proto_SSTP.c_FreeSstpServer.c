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
struct TYPE_4__ {int /*<<< orphan*/  TubeRecv; int /*<<< orphan*/  TubeSend; int /*<<< orphan*/  Cedar; int /*<<< orphan*/  Interrupt; int /*<<< orphan*/  SockEvent; int /*<<< orphan*/  SendQueue; int /*<<< orphan*/  RecvQueue; int /*<<< orphan*/  PPPThread; } ;
typedef  TYPE_1__ SSTP_SERVER ;
typedef  int /*<<< orphan*/  BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeBlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeInterruptManager (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetNext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  ReleaseCedar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSockEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseTube (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TubeDisconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void FreeSstpServer(SSTP_SERVER *s)
{
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	TubeDisconnect(s->TubeRecv);
	TubeDisconnect(s->TubeSend);

	WaitThread(s->PPPThread, INFINITE);
	ReleaseThread(s->PPPThread);

	while (true)
	{
		BLOCK *b = GetNext(s->RecvQueue);

		if (b == NULL)
		{
			break;
		}

		FreeBlock(b);
	}

	while (true)
	{
		BLOCK *b = GetNext(s->SendQueue);

		if (b == NULL)
		{
			break;
		}

		FreeBlock(b);
	}

	ReleaseQueue(s->RecvQueue);
	ReleaseQueue(s->SendQueue);

	ReleaseSockEvent(s->SockEvent);

	FreeInterruptManager(s->Interrupt);

	ReleaseCedar(s->Cedar);

	ReleaseTube(s->TubeSend);
	ReleaseTube(s->TubeRecv);

	Free(s);
}