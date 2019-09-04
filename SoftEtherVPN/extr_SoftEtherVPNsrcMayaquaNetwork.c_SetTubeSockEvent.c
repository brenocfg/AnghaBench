#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  ref; } ;
struct TYPE_8__ {scalar_t__ IndexInTubePair; int /*<<< orphan*/  Lock; TYPE_1__* TubePairData; TYPE_3__* SockEvent; } ;
struct TYPE_7__ {int /*<<< orphan*/  Lock; TYPE_3__* SockEvent2; TYPE_3__* SockEvent1; } ;
typedef  TYPE_1__ TUBEPAIR_DATA ;
typedef  TYPE_2__ TUBE ;
typedef  TYPE_3__ SOCK_EVENT ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSockEvent (TYPE_3__*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

void SetTubeSockEvent(TUBE *t, SOCK_EVENT *e)
{
	// Validate arguments
	if (t == NULL)
	{
		return;
	}

	Lock(t->Lock);
	{
		TUBEPAIR_DATA *d;

		if (t->SockEvent != e)
		{
			if (t->SockEvent != NULL)
			{
				ReleaseSockEvent(t->SockEvent);
			}

			if (e != NULL)
			{
				AddRef(e->ref);
			}

			t->SockEvent = e;
		}

		d = t->TubePairData;

		if (d != NULL)
		{
			Lock(d->Lock);
			{
				SOCK_EVENT **sep = (t->IndexInTubePair == 0 ? &d->SockEvent1 : &d->SockEvent2);

				if (*sep != e)
				{
					if (*sep != NULL)
					{
						ReleaseSockEvent(*sep);
					}

					if (e != NULL)
					{
						AddRef(e->ref);
					}

					*sep = e;
				}
			}
			Unlock(d->Lock);
		}
	}
	Unlock(t->Lock);
}