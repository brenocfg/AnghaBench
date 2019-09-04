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
struct TYPE_4__ {int /*<<< orphan*/  Lock; int /*<<< orphan*/  TubePairData; int /*<<< orphan*/  SockEvent; int /*<<< orphan*/  Event; int /*<<< orphan*/  Queue; } ;
typedef  int /*<<< orphan*/  TUBEDATA ;
typedef  TYPE_1__ TUBE ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeTubeData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetNext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSockEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseTubePairData (int /*<<< orphan*/ ) ; 

void CleanupTube(TUBE *t)
{
	// Validate arguments
	if (t == NULL)
	{
		return;
	}

	while (true)
	{
		TUBEDATA *d = GetNext(t->Queue);
		if (d == NULL)
		{
			break;
		}

		FreeTubeData(d);
	}

	ReleaseQueue(t->Queue);
	ReleaseEvent(t->Event);
	ReleaseSockEvent(t->SockEvent);

	ReleaseTubePairData(t->TubePairData);

	DeleteLock(t->Lock);

	Free(t);
}