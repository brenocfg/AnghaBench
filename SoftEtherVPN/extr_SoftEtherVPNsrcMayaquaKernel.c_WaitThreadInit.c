#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  init_finished_event; } ;
typedef  TYPE_1__ THREAD ;

/* Variables and functions */
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_WAITFORTHREAD_COUNT ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void WaitThreadInit(THREAD *t)
{
	// Validate arguments
	if (t == NULL)
	{
		return;
	}

	// KS
	KS_INC(KS_WAITFORTHREAD_COUNT);

	// Wait
	Wait(t->init_finished_event, INFINITE);
}