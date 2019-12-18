#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  ref; } ;
struct TYPE_7__ {int /*<<< orphan*/  LastCommTime; int /*<<< orphan*/  LastRecvTime; int /*<<< orphan*/  EstablishedTick; void* SendFifo; void* RecvFifo; TYPE_2__* Sock; } ;
typedef  TYPE_1__ TCPSOCK ;
typedef  TYPE_2__ SOCK ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 void* NewFifo () ; 
 int /*<<< orphan*/  SetTimeout (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMEOUT_INFINITE ; 
 int /*<<< orphan*/  Tick64 () ; 
 TYPE_1__* ZeroMalloc (int) ; 

TCPSOCK *NewTcpSock(SOCK *s)
{
	TCPSOCK *ts;
	// Validate arguments
	if (s == NULL)
	{
		return NULL;
	}

	ts = ZeroMalloc(sizeof(TCPSOCK));

	ts->Sock = s;
	AddRef(s->ref);

	ts->RecvFifo = NewFifo();
	ts->SendFifo = NewFifo();
	ts->EstablishedTick = ts->LastRecvTime = ts->LastCommTime = Tick64();

	// Unset the time-out value
	SetTimeout(s, TIMEOUT_INFINITE);

	return ts;
}