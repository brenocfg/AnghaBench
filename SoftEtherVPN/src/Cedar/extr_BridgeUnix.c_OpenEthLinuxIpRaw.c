#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int pipe_read; int pipe_write; int SpecialFlag; int pipe_special_read2; int pipe_special_read3; } ;
struct TYPE_10__ {int socket; } ;
struct TYPE_9__ {int IsRawIpMode; int* RawIpMyMacAddr; int RawIP_TmpBufferSize; int /*<<< orphan*/  RawIP_TmpBuffer; int /*<<< orphan*/  RawIpSendQueue; int /*<<< orphan*/  YourIP; int /*<<< orphan*/  MyIP; TYPE_3__* RawIcmp; TYPE_6__* Cancel; TYPE_3__* RawUdp; TYPE_3__* RawTcp; void* Title; void* Name; } ;
typedef  TYPE_1__ ETH ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_SPECIAL_IPRAW_NAME ; 
 int /*<<< orphan*/  ClearSockDfBit (TYPE_3__*) ; 
 void* CopyStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  IPPROTO_ICMP ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int IsRawIpBridgeSupported () ; 
 int /*<<< orphan*/  MAKE_SPECIAL_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Malloc (int) ; 
 TYPE_6__* NewCancel () ; 
 int /*<<< orphan*/  NewQueueFast () ; 
 void* NewUDP4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_3__*) ; 
 int /*<<< orphan*/  SetIP (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  SetRawSockHeaderIncludeOption (TYPE_3__*,int) ; 
 int /*<<< orphan*/  UnixDeletePipe (int,int) ; 
 int /*<<< orphan*/  UnixSetSocketNonBlockingMode (int,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 

ETH *OpenEthLinuxIpRaw()
{
	ETH *e;

	if (IsRawIpBridgeSupported() == false)
	{
		return NULL;
	}

	e = ZeroMalloc(sizeof(ETH));

	e->IsRawIpMode = true;

	e->RawTcp = NewUDP4(MAKE_SPECIAL_PORT(IPPROTO_TCP), NULL);
	e->RawUdp = NewUDP4(MAKE_SPECIAL_PORT(IPPROTO_UDP), NULL);
	e->RawIcmp = NewUDP4(MAKE_SPECIAL_PORT(IPPROTO_ICMP), NULL);

	if (e->RawTcp == NULL || e->RawUdp == NULL || e->RawIcmp == NULL)
	{
		ReleaseSock(e->RawTcp);
		ReleaseSock(e->RawUdp);
		ReleaseSock(e->RawIcmp);

		Free(e);
		return NULL;
	}

	ClearSockDfBit(e->RawTcp);
	ClearSockDfBit(e->RawUdp);
	ClearSockDfBit(e->RawIcmp);

	SetRawSockHeaderIncludeOption(e->RawTcp, true);
	SetRawSockHeaderIncludeOption(e->RawUdp, true);
	SetRawSockHeaderIncludeOption(e->RawIcmp, true);

	e->Name = CopyStr(BRIDGE_SPECIAL_IPRAW_NAME);
	e->Title = CopyStr(BRIDGE_SPECIAL_IPRAW_NAME);
	e->Cancel = NewCancel();

	UnixDeletePipe(e->Cancel->pipe_read, e->Cancel->pipe_write);
	e->Cancel->pipe_read = e->Cancel->pipe_write = -1;

	UnixSetSocketNonBlockingMode(e->RawTcp->socket, true);
	UnixSetSocketNonBlockingMode(e->RawUdp->socket, true);
	UnixSetSocketNonBlockingMode(e->RawIcmp->socket, true);

	e->Cancel->SpecialFlag = true;
	e->Cancel->pipe_read = e->RawTcp->socket;
	e->Cancel->pipe_special_read2 = e->RawUdp->socket;
	e->Cancel->pipe_special_read3 = e->RawIcmp->socket;

	e->RawIpMyMacAddr[2] = 0x01;
	e->RawIpMyMacAddr[5] = 0x01;

	SetIP(&e->MyIP, 10, 171, 7, 253);
	SetIP(&e->YourIP, 10, 171, 7, 254);

	e->RawIpSendQueue = NewQueueFast();

	e->RawIP_TmpBufferSize = 67000;
	e->RawIP_TmpBuffer = Malloc(e->RawIP_TmpBufferSize);

	return e;
}