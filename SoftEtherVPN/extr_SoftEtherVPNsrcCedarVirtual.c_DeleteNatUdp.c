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
struct TYPE_8__ {int /*<<< orphan*/  NatTable; } ;
typedef  TYPE_1__ VH ;
struct TYPE_9__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * Sock; int /*<<< orphan*/  UdpSendQueue; int /*<<< orphan*/  UdpRecvQueue; int /*<<< orphan*/  Id; } ;
typedef  TYPE_2__ NAT_ENTRY ;
typedef  int /*<<< orphan*/  BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeBlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetNext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLog (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 

void DeleteNatUdp(VH *v, NAT_ENTRY *n)
{
	BLOCK *block;
	// Validate arguments
	if (v == NULL || n == NULL)
	{
		return;
	}

	NLog(v, "LH_NAT_UDP_DELETED", n->Id);

	// Release all queues
	while (block = GetNext(n->UdpRecvQueue))
	{
		FreeBlock(block);
	}
	ReleaseQueue(n->UdpRecvQueue);
	while (block = GetNext(n->UdpSendQueue))
	{
		FreeBlock(block);
	}
	ReleaseQueue(n->UdpSendQueue);

	// Release the socket
	if (n->Sock != NULL)
	{
		Disconnect(n->Sock);
		ReleaseSock(n->Sock);
		n->Sock = NULL;
	}

	DeleteLock(n->lock);

	// Remove from the table
	Delete(v->NatTable, n);

	// Release the memory
	Free(n);

	Debug("NAT: DeleteNatUdp\n");

}