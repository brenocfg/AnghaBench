#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_15__ {int /*<<< orphan*/  AdminList; scalar_t__ Halt; TYPE_1__* AdminListenSock; int /*<<< orphan*/  HaltEvent; } ;
struct TYPE_14__ {TYPE_1__* Sock; int /*<<< orphan*/ * Thread; TYPE_3__* Nat; } ;
struct TYPE_13__ {int /*<<< orphan*/  ref; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ SOCK ;
typedef  TYPE_2__ NAT_ADMIN ;
typedef  TYPE_3__ NAT ;

/* Variables and functions */
 TYPE_1__* Accept (TYPE_1__*) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEFAULT_NAT_ADMIN_PORT ; 
 int /*<<< orphan*/  Disconnect (TYPE_1__*) ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 int /*<<< orphan*/  INFINITE ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 TYPE_1__* Listen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAT_ADMIN_PORT_LISTEN_INTERVAL ; 
 int /*<<< orphan*/  NewList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  NiAdminThread ; 
 int /*<<< orphan*/  NoticeThreadInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ *) ; 
 TYPE_2__* ZeroMalloc (int) ; 

void NiListenThread(THREAD *thread, void *param)
{
	NAT *n = (NAT *)param;
	SOCK *a;
	UINT i;
	bool b = false;
	// Validate arguments
	if (thread == NULL || param == NULL)
	{
		return;
	}

	// Initialize the management list
	n->AdminList = NewList(NULL);

	while (true)
	{
		a = Listen(DEFAULT_NAT_ADMIN_PORT);
		if (b == false)
		{
			b = true;
			NoticeThreadInit(thread);
		}
		if (a != NULL)
		{
			break;
		}

		Wait(n->HaltEvent, NAT_ADMIN_PORT_LISTEN_INTERVAL);
		if (n->Halt)
		{
			return;
		}
	}

	n->AdminListenSock = a;
	AddRef(a->ref);

	// Waiting
	while (true)
	{
		SOCK *s = Accept(a);
		THREAD *t;
		NAT_ADMIN *admin;
		if (s == NULL)
		{
			break;
		}
		if (n->Halt)
		{
			ReleaseSock(s);
			break;
		}

		admin = ZeroMalloc(sizeof(NAT_ADMIN));
		admin->Nat = n;
		admin->Sock = s;
		t = NewThread(NiAdminThread, admin);
		WaitThreadInit(t);
		ReleaseThread(t);
	}

	// Disconnect all management connections
	LockList(n->AdminList);
	{
		for (i = 0;i < LIST_NUM(n->AdminList);i++)
		{
			NAT_ADMIN *a = LIST_DATA(n->AdminList, i);
			Disconnect(a->Sock);
			WaitThread(a->Thread, INFINITE);
			ReleaseThread(a->Thread);
			ReleaseSock(a->Sock);
			Free(a);
		}
	}
	UnlockList(n->AdminList);

	ReleaseList(n->AdminList);

	ReleaseSock(a);
}