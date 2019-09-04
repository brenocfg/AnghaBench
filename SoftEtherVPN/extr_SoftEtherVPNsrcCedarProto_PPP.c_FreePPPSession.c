#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  IntParam2; int /*<<< orphan*/  IntParam1; } ;
struct TYPE_8__ {int /*<<< orphan*/ * Ipc; TYPE_2__* TubeSend; TYPE_2__* TubeRecv; int /*<<< orphan*/  Cedar; int /*<<< orphan*/  FlushList; int /*<<< orphan*/  DisconnectCauseDirection; int /*<<< orphan*/  DisconnectCauseCode; } ;
typedef  TYPE_1__ PPP_SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeIPC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeTubeFlushList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPPFreeEapClient (TYPE_1__*) ; 
 int /*<<< orphan*/  PPPStoreLastPacket (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseCedar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseTube (TYPE_2__*) ; 
 int /*<<< orphan*/  TubeDisconnect (TYPE_2__*) ; 

void FreePPPSession(PPP_SESSION *p)
{
	// Validate arguments
	if (p == NULL)
	{
		return;
	}

	if (p->TubeRecv != NULL)
	{
		// Record the PPP disconnect reason code for L2TP
		p->TubeRecv->IntParam1 = p->DisconnectCauseCode;
		p->TubeRecv->IntParam2 = p->DisconnectCauseDirection;
	}

	FreeTubeFlushList(p->FlushList);

	TubeDisconnect(p->TubeRecv);
	TubeDisconnect(p->TubeSend);

	ReleaseCedar(p->Cedar);

	ReleaseTube(p->TubeRecv);
	ReleaseTube(p->TubeSend);

	PPPStoreLastPacket(p, NULL);

	if (p->Ipc != NULL)
	{
		FreeIPC(p->Ipc);
	}

	PPPFreeEapClient(p);

	Free(p);
}