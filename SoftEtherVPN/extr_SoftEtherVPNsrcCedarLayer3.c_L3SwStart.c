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
struct TYPE_4__ {int Active; int Halt; int /*<<< orphan*/  lock; int /*<<< orphan*/  Thread; int /*<<< orphan*/  IfList; } ;
typedef  TYPE_1__ L3SW ;

/* Variables and functions */
 int /*<<< orphan*/  L3SwThread ; 
 int LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewThread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ ) ; 

void L3SwStart(L3SW *s)
{
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	Lock(s->lock);
	{
		if (s->Active == false)
		{
			// Start if there is registered interface
			if (LIST_NUM(s->IfList) >= 1)
			{
				s->Halt = false;

				// Create a thread
				s->Thread = NewThread(L3SwThread, s);
				WaitThreadInit(s->Thread);
			}
		}
	}
	Unlock(s->lock);
}