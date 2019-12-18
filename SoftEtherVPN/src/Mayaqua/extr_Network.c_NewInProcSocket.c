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
struct TYPE_8__ {int Connected; int /*<<< orphan*/  InProcRecvFifo; TYPE_1__* RecvTube; TYPE_1__* SendTube; int /*<<< orphan*/  Type; } ;
struct TYPE_7__ {int /*<<< orphan*/  Ref; } ;
typedef  TYPE_1__ TUBE ;
typedef  TYPE_2__ SOCK ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewFifo () ; 
 TYPE_2__* NewSock () ; 
 int /*<<< orphan*/  SOCK_INPROC ; 

SOCK *NewInProcSocket(TUBE *tube_send, TUBE *tube_recv)
{
	SOCK *s;
	// Validate arguments
	if (tube_recv == NULL || tube_send == NULL)
	{
		return NULL;
	}

	s = NewSock();

	s->Type = SOCK_INPROC;

	s->SendTube = tube_send;
	s->RecvTube = tube_recv;

	AddRef(tube_send->Ref);
	AddRef(tube_recv->Ref);

	s->InProcRecvFifo = NewFifo();

	s->Connected = true;

	return s;
}