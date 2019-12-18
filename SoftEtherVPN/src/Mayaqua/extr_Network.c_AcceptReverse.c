#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ Type; int ListenMode; int /*<<< orphan*/  ReverseAcceptEvent; int /*<<< orphan*/  UnderlayProtocol; int /*<<< orphan*/  ReverseAcceptQueue; scalar_t__ CancelAccept; scalar_t__ Disconnecting; } ;
typedef  TYPE_1__ SOCK ;

/* Variables and functions */
 TYPE_1__* GetNext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  LockQueue (int /*<<< orphan*/ ) ; 
 scalar_t__ SOCK_REVERSE_LISTEN ; 
 int /*<<< orphan*/  SOCK_UNDERLAY_AZURE ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

SOCK *AcceptReverse(SOCK *s)
{
	// Validate arguments
	if (s == NULL || s->Type != SOCK_REVERSE_LISTEN || s->ListenMode == false)
	{
		return NULL;
	}

	while (true)
	{
		SOCK *ret;
		if (s->Disconnecting || s->CancelAccept)
		{
			return NULL;
		}

		LockQueue(s->ReverseAcceptQueue);
		{
			ret = GetNext(s->ReverseAcceptQueue);
		}
		UnlockQueue(s->ReverseAcceptQueue);

		if (ret != NULL)
		{
			StrCpy(ret->UnderlayProtocol, sizeof(ret->UnderlayProtocol), SOCK_UNDERLAY_AZURE);

			return ret;
		}

		Wait(s->ReverseAcceptEvent, INFINITE);
	}
}