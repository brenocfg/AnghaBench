#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_7__ {int /*<<< orphan*/  BulkRecvKey; int /*<<< orphan*/  BulkSendKey; int /*<<< orphan*/  SendFifo; int /*<<< orphan*/  RecvFifo; int /*<<< orphan*/  ReplyAckList; int /*<<< orphan*/ * TcpSock; int /*<<< orphan*/  RecvSegmentList; int /*<<< orphan*/  SendSegmentList; } ;
typedef  TYPE_1__ RUDP_SESSION ;
typedef  TYPE_1__ RUDP_SEGMENT ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseFifo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseInt64List (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSharedBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 

void RUDPFreeSession(RUDP_SESSION *se)
{
	UINT i;
	// Validate arguments
	if (se == NULL)
	{
		return;
	}

	Debug("RUDPFreeSession %X\n", se);

	for (i = 0;i < LIST_NUM(se->SendSegmentList);i++)
	{
		RUDP_SEGMENT *s = LIST_DATA(se->SendSegmentList, i);

		Free(s);
	}

	ReleaseList(se->SendSegmentList);

	for (i = 0;i < LIST_NUM(se->RecvSegmentList);i++)
	{
		RUDP_SEGMENT *s = LIST_DATA(se->RecvSegmentList, i);

		Free(s);
	}

	ReleaseList(se->RecvSegmentList);

	if (se->TcpSock != NULL)
	{
		Disconnect(se->TcpSock);
		ReleaseSock(se->TcpSock);
	}

	ReleaseInt64List(se->ReplyAckList);

	ReleaseFifo(se->RecvFifo);
	ReleaseFifo(se->SendFifo);

	ReleaseSharedBuffer(se->BulkSendKey);
	ReleaseSharedBuffer(se->BulkRecvKey);

	Free(se);
}