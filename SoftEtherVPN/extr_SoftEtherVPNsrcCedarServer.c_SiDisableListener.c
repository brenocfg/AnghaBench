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
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int Enabled; int /*<<< orphan*/ * Listener; } ;
typedef  TYPE_1__ SERVER_LISTENER ;
typedef  int /*<<< orphan*/  SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  ReleaseListener (int /*<<< orphan*/ *) ; 
 TYPE_1__* SiGetListener (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  StopListener (int /*<<< orphan*/ *) ; 

bool SiDisableListener(SERVER *s, UINT port)
{
	SERVER_LISTENER *e;
	// Validate arguments
	if (s == NULL || port == 0)
	{
		return false;
	}

	// Get the listener
	e = SiGetListener(s, port);
	if (e == NULL)
	{
		return false;
	}

	if (e->Enabled == false || e->Listener == NULL)
	{
		// Already stopped
		return true;
	}

	// Stop the listener
	StopListener(e->Listener);

	// Release the listener
	ReleaseListener(e->Listener);
	e->Listener = NULL;

	e->Enabled = false;

	return true;
}