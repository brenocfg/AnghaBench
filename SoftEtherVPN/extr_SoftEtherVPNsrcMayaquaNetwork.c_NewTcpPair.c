#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ LocalPort; scalar_t__ RemotePort; TYPE_1__* BulkRecvTube; TYPE_1__* BulkSendTube; } ;
struct TYPE_13__ {int /*<<< orphan*/  Ref; } ;
typedef  TYPE_1__ TUBE ;
typedef  int /*<<< orphan*/  TCP_PAIR_HEADER ;
typedef  int /*<<< orphan*/  SOCK_EVENT ;
typedef  TYPE_2__ SOCK ;

/* Variables and functions */
 TYPE_2__* Accept (TYPE_2__*) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 TYPE_2__* Connect (char*,scalar_t__) ; 
 TYPE_2__* ListenAnyPortEx2 (int,int) ; 
 int /*<<< orphan*/ * NewSockEvent () ; 
 int /*<<< orphan*/  NewTubePair (TYPE_1__**,TYPE_1__**,int) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_2__*) ; 
 int /*<<< orphan*/  ReleaseSockEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetTubeSockEvent (TYPE_1__*,int /*<<< orphan*/ *) ; 

bool NewTcpPair(SOCK **s1, SOCK **s2)
{
	SOCK *a;
	SOCK *s, *c;
	TUBE *t1, *t2;
	SOCK_EVENT *e1, *e2;
	// Validate arguments
	if (s1 == NULL || s2 == NULL)
	{
		return false;
	}

	a = ListenAnyPortEx2(true, true);
	if (a == NULL)
	{
		return false;
	}

	c = Connect("127.0.0.1", a->LocalPort);
	if (c == NULL)
	{
		ReleaseSock(a);
		return false;
	}

	s = Accept(a);
	if (s == NULL)
	{
		ReleaseSock(c);
		ReleaseSock(a);
		return false;
	}

	ReleaseSock(a);

	if ((s->LocalPort != c->RemotePort) || (s->RemotePort != c->LocalPort))
	{
		ReleaseSock(s);
		ReleaseSock(c);
		return false;
	}

	NewTubePair(&t1, &t2, sizeof(TCP_PAIR_HEADER));

	// Creating a socket event
	e1 = NewSockEvent();
	e2 = NewSockEvent();

	SetTubeSockEvent(t1, e1);
	SetTubeSockEvent(t2, e2);

	AddRef(t1->Ref);
	AddRef(t2->Ref);
	s->BulkRecvTube = c->BulkSendTube = t1;
	s->BulkSendTube = c->BulkRecvTube = t2;

	ReleaseSockEvent(e1);
	ReleaseSockEvent(e2);

	*s1 = s;
	*s2 = c;

	return true;
}