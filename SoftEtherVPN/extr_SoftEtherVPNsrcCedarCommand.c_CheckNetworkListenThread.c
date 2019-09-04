#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  c ;
typedef  int /*<<< orphan*/  X ;
typedef  int UINT ;
struct TYPE_12__ {TYPE_1__* ListenSocket; } ;
struct TYPE_11__ {int /*<<< orphan*/ * x; int /*<<< orphan*/ * k; TYPE_1__* s; } ;
struct TYPE_10__ {int /*<<< orphan*/  ref; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ SOCK ;
typedef  int /*<<< orphan*/  NAME ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  K ;
typedef  TYPE_2__ CHECK_NETWORK_2 ;
typedef  TYPE_3__ CHECK_NETWORK_1 ;

/* Variables and functions */
 TYPE_1__* Accept (TYPE_1__*) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckNetworkAcceptThread ; 
 int /*<<< orphan*/  FreeK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ *,int) ; 
 int LIST_NUM (int /*<<< orphan*/ *) ; 
 TYPE_1__* Listen (int) ; 
 int /*<<< orphan*/ * NewList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewName (char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/ * NewRootX (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  NoticeThreadInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RsaGen (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

void CheckNetworkListenThread(THREAD *thread, void *param)
{
	CHECK_NETWORK_1 *c = (CHECK_NETWORK_1 *)param;
	SOCK *s;
	UINT i;
	K *pub, *pri;
	X *x;
	LIST *o = NewList(NULL);
	NAME *name = NewName(L"Test", L"Test", L"Test", L"JP", L"Ibaraki", L"Tsukuba");

	RsaGen(&pri, &pub, 1024);
	x = NewRootX(pub, pri, name, 1000, NULL);

	FreeName(name);

	for (i = 1025;;i++)
	{
		s = Listen(i);
		if (s != NULL)
		{
			break;
		}
	}

	c->ListenSocket = s;
	AddRef(s->ref);

	NoticeThreadInit(thread);

	while (true)
	{
		SOCK *new_sock = Accept(s);

		if (new_sock == NULL)
		{
			break;
		}
		else
		{
			CHECK_NETWORK_2 c;
			THREAD *t;

			Zero(&c, sizeof(c));
			c.s = new_sock;
			c.k = pri;
			c.x = x;

			t = NewThread(CheckNetworkAcceptThread, &c);
			Insert(o, t);
		}
	}

	for (i = 0;i < LIST_NUM(o);i++)
	{
		THREAD *t = LIST_DATA(o, i);
		WaitThread(t, INFINITE);
		ReleaseThread(t);
	}

	FreeK(pri);
	FreeK(pub);

	FreeX(x);

	ReleaseSock(s);
	ReleaseList(o);
}