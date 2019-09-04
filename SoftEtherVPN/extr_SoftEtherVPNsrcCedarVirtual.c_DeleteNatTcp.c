#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  NatTable; } ;
typedef  TYPE_1__ VH ;
typedef  scalar_t__ UINT ;
struct TYPE_11__ {int NatTcpCancelFlag; int /*<<< orphan*/  lock; int /*<<< orphan*/ * RecvFifo; int /*<<< orphan*/ * SendFifo; int /*<<< orphan*/ * TcpRecvList; int /*<<< orphan*/ * TcpRecvWindow; int /*<<< orphan*/ * Sock; int /*<<< orphan*/ * NatTcpConnectThread; int /*<<< orphan*/  Id; } ;
typedef  TYPE_2__ NAT_ENTRY ;
typedef  TYPE_2__ IP_PART ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 int /*<<< orphan*/  INFINITE ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NLog (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseFifo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void DeleteNatTcp(VH *v, NAT_ENTRY *n)
{
	// Validate arguments
	if (v == NULL || n == NULL)
	{
		return;
	}

	NLog(v, "LH_NAT_TCP_DELETED", n->Id);

	// Shutdown of connection thread
	if (n->NatTcpConnectThread != NULL)
	{
		n->NatTcpCancelFlag = true;

		WaitThread(n->NatTcpConnectThread, INFINITE);
		ReleaseThread(n->NatTcpConnectThread);
		n->NatTcpConnectThread = NULL;
	}
	if (n->Sock != NULL)
	{
		// Disconnect the socket
		Disconnect(n->Sock);
		ReleaseSock(n->Sock);
		n->Sock = NULL;
	}

	// Release the window memory
	if (n->TcpRecvWindow != NULL)
	{
		ReleaseFifo(n->TcpRecvWindow);
		n->TcpRecvWindow = NULL;
	}

	// Release the window reception list
	if (n->TcpRecvList != NULL)
	{
		UINT i;
		for (i = 0;i < LIST_NUM(n->TcpRecvList);i++)
		{
			IP_PART *p = LIST_DATA(n->TcpRecvList, i);
			Free(p);
		}
		ReleaseList(n->TcpRecvList);
		n->TcpRecvList = NULL;
	}

	// FIFO release
	ReleaseFifo(n->SendFifo);
	ReleaseFifo(n->RecvFifo);

	// Delete from the NAT entry
	Delete(v->NatTable, n);

	DeleteLock(n->lock);

	// Release the memory
	Free(n);

	Debug("NAT_ENTRY: DeleteNatTcp\n");
}