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
struct TYPE_4__ {int /*<<< orphan*/  Queue; } ;
typedef  int /*<<< orphan*/  TUBEDATA ;
typedef  TYPE_1__ TUBE ;

/* Variables and functions */
 int /*<<< orphan*/ * GetNext (int /*<<< orphan*/ ) ; 
 int IsTubeConnected (TYPE_1__*) ; 
 int /*<<< orphan*/  LockQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockQueue (int /*<<< orphan*/ ) ; 

TUBEDATA *TubeRecvAsync(TUBE *t)
{
	TUBEDATA *d;
	// Validate arguments
	if (t == NULL)
	{
		return NULL;
	}

	if (IsTubeConnected(t) == false)
	{
		return NULL;
	}

	LockQueue(t->Queue);
	{
		d = GetNext(t->Queue);
	}
	UnlockQueue(t->Queue);

	return d;
}