#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  DataSize; int /*<<< orphan*/  Data; scalar_t__ IsControl; } ;
struct TYPE_5__ {int FlushRecvTube; int /*<<< orphan*/  TubeRecv; int /*<<< orphan*/  ClientCipherName; int /*<<< orphan*/  ClientHostName; int /*<<< orphan*/  TubeSend; int /*<<< orphan*/  ServerPort; int /*<<< orphan*/  ServerIp; int /*<<< orphan*/  ClientPort; int /*<<< orphan*/  ClientIp; int /*<<< orphan*/  Cedar; int /*<<< orphan*/ * PPPThread; } ;
typedef  TYPE_1__ SSTP_SERVER ;
typedef  TYPE_2__ SSTP_PACKET ;

/* Variables and functions */
 int /*<<< orphan*/ * NewPPPSession (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSTP_IPC_CLIENT_NAME ; 
 int /*<<< orphan*/  SSTP_IPC_POSTFIX ; 
 int /*<<< orphan*/  TubeSendEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void SstpProcessDataPacket(SSTP_SERVER *s, SSTP_PACKET *p)
{
	// Validate arguments
	if (s == NULL || p == NULL || p->IsControl)
	{
		return;
	}

	//Debug("SSTP Data Packet Recv: Size = %u\n", p->DataSize);

	if (s->PPPThread == NULL)
	{
		// Create a thread to initialize the new PPP module
		s->PPPThread = NewPPPSession(s->Cedar, &s->ClientIp, s->ClientPort, &s->ServerIp, s->ServerPort,
			s->TubeSend, s->TubeRecv, SSTP_IPC_POSTFIX, SSTP_IPC_CLIENT_NAME,
			s->ClientHostName, s->ClientCipherName, 0);
	}

	// Pass the received data to the PPP module
	TubeSendEx(s->TubeRecv, p->Data, p->DataSize, NULL, true);
	s->FlushRecvTube = true;
}