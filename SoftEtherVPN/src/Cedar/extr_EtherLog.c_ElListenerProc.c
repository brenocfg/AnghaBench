#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rand ;
typedef  int /*<<< orphan*/  pass2 ;
typedef  int /*<<< orphan*/  code ;
typedef  int UCHAR ;
struct TYPE_21__ {int /*<<< orphan*/  AdminThreadList; int /*<<< orphan*/  AdminSockList; int /*<<< orphan*/  HashedPassword; } ;
struct TYPE_20__ {TYPE_2__* s; TYPE_1__* r; } ;
struct TYPE_19__ {int /*<<< orphan*/  ref; } ;
struct TYPE_18__ {scalar_t__ ThreadParam; } ;
typedef  TYPE_2__ THREAD ;
typedef  TYPE_3__ TCP_ACCEPTED_PARAM ;
typedef  TYPE_2__ SOCK ;
typedef  int /*<<< orphan*/  RPC ;
typedef  TYPE_5__ EL ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 scalar_t__ Cmp (int*,int*,int) ; 
 scalar_t__ Delete (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  Disconnect (TYPE_2__*) ; 
 int /*<<< orphan*/  ElRpcServer ; 
 int Endian32 (int) ; 
 int INFINITE ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NoticeThreadInit (TYPE_2__*) ; 
 int /*<<< orphan*/  Rand (int*,int) ; 
 int /*<<< orphan*/  RecvAll (TYPE_2__*,int*,int,int) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_2__*) ; 
 int /*<<< orphan*/  ReleaseThread (TYPE_2__*) ; 
 int /*<<< orphan*/  RpcFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RpcServer (int /*<<< orphan*/ *) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  SecurePassword (int*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  SendAll (TYPE_2__*,int*,int,int) ; 
 int /*<<< orphan*/  SetTimeout (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * StartRpcServer (TYPE_2__*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (int*,int) ; 

void ElListenerProc(THREAD *thread, void *param)
{
	TCP_ACCEPTED_PARAM *data = (TCP_ACCEPTED_PARAM *)param;
	EL *e;
	SOCK *s;
	UCHAR rand[SHA1_SIZE];
	UCHAR pass1[SHA1_SIZE], pass2[SHA1_SIZE];
	// Validate arguments
	if (data == NULL || thread == NULL)
	{
		return;
	}

	e = (EL *)data->r->ThreadParam;
	s = data->s;
	AddRef(s->ref);
	SetTimeout(s, 5000);
	LockList(e->AdminThreadList);
	{
		AddRef(thread->ref);
		AddRef(s->ref);
		Insert(e->AdminThreadList, thread);
		Insert(e->AdminSockList, s);
	}
	UnlockList(e->AdminThreadList);
	NoticeThreadInit(thread);

	// Submit a challenge
	Rand(rand, sizeof(rand));
	SendAll(s, rand, sizeof(rand), false);

	// Receive a response
	SecurePassword(pass1, e->HashedPassword, rand);
	Zero(pass2, sizeof(pass2));
	(void)RecvAll(s, pass2, sizeof(pass2), false);

	if (Cmp(pass1, pass2, SHA1_SIZE) != 0)
	{
		// Password incorrect
		bool code = false;
		code = Endian32(code);
		SendAll(s, &code, sizeof(code), false);
	}
	else
	{
		// Password match
		bool code = true;
		RPC *r;

		code = Endian32(code);
		SendAll(s, &code, sizeof(code), false);

		SetTimeout(s, INFINITE);

		// Start operation as a RPC server
		r = StartRpcServer(s, ElRpcServer, e);
		RpcServer(r);
		RpcFree(r);
	}

	Disconnect(s);
	ReleaseSock(s);

	LockList(e->AdminThreadList);
	{
		if (Delete(e->AdminThreadList, thread))
		{
			ReleaseThread(thread);
		}
		if (Delete(e->AdminSockList, s))
		{
			ReleaseSock(s);
		}
	}
	UnlockList(e->AdminThreadList);
}