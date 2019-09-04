#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  EVENT ;

/* Variables and functions */
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KS_FREEEVENT_COUNT ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSFreeEvent (int /*<<< orphan*/ *) ; 

void CleanupEvent(EVENT *e)
{
	// Validate arguments
	if (e == NULL)
	{
		return;
	}

	// Release event
	OSFreeEvent(e);

	// Memory release
	Free(e);

	// KS
	KS_INC(KS_FREEEVENT_COUNT);
}