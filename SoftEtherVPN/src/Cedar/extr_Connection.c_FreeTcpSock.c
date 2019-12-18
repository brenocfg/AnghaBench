#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ RecvKey; scalar_t__ SendKey; int /*<<< orphan*/  SendFifo; int /*<<< orphan*/  RecvFifo; int /*<<< orphan*/  Sock; } ;
typedef  TYPE_1__ TCPSOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeCrypt (scalar_t__) ; 
 int /*<<< orphan*/  ReleaseFifo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ ) ; 

void FreeTcpSock(TCPSOCK *ts)
{
	// Validate arguments
	if (ts == NULL)
	{
		return;
	}

	Disconnect(ts->Sock);
	ReleaseSock(ts->Sock);
	ReleaseFifo(ts->RecvFifo);
	ReleaseFifo(ts->SendFifo);

	if (ts->SendKey)
	{
		FreeCrypt(ts->SendKey);
	}
	if (ts->RecvKey)
	{
		FreeCrypt(ts->RecvKey);
	}

	Free(ts);
}