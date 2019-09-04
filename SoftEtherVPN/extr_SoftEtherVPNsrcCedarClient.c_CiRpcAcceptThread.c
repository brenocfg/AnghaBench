#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  RpcConnectionList; } ;
struct TYPE_12__ {int /*<<< orphan*/  Thread; TYPE_1__* Sock; TYPE_3__* Client; } ;
struct TYPE_11__ {int /*<<< orphan*/  ref; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ SOCK ;
typedef  TYPE_2__ CLIENT_RPC_CONNECTION ;
typedef  TYPE_3__ CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CiRpcAccepted (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  Disconnect (TYPE_1__*) ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NoticeThreadInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void CiRpcAcceptThread(THREAD *thread, void *param)
{
	CLIENT_RPC_CONNECTION *conn;
	CLIENT *c;
	SOCK *s;
	// Validate arguments
	if (thread == NULL || param == NULL)
	{
		return;
	}

	conn = (CLIENT_RPC_CONNECTION *)param;
	s = conn->Sock;
	c = conn->Client;
	AddRef(s->ref);

	// Add to the RPC connection list
	LockList(c->RpcConnectionList);
	{
		Add(c->RpcConnectionList, conn);
	}
	UnlockList(c->RpcConnectionList);

	NoticeThreadInit(thread);

	// Main process
	CiRpcAccepted(c, s);

	// Release from the connection list
	LockList(c->RpcConnectionList);
	{
		Delete(c->RpcConnectionList, conn);
	}
	UnlockList(c->RpcConnectionList);

	ReleaseSock(conn->Sock);
	ReleaseThread(conn->Thread);
	Free(conn);

	Disconnect(s);
	ReleaseSock(s);
}