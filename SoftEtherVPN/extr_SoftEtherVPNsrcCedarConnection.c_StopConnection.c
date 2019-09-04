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
struct TYPE_3__ {int Halt; int /*<<< orphan*/  Thread; int /*<<< orphan*/  FirstSock; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ CONNECTION ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void StopConnection(CONNECTION *c, bool no_wait)
{
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	Debug("Stop Connection: %s\n", c->Name);

	// Stop flag
	c->Halt = true;
	Disconnect(c->FirstSock);

	if (no_wait == false)
	{
		// Wait until the thread terminates
		WaitThread(c->Thread, INFINITE);
	}
}