#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ref; } ;
struct TYPE_6__ {int UserCanceled; int CancelConnect; int Halt; int ForceStopFlag; int /*<<< orphan*/  Thread; TYPE_2__* Connection; int /*<<< orphan*/  HaltEvent; int /*<<< orphan*/  Cancel1; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ SESSION ;
typedef  TYPE_2__ CONNECTION ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseConnection (TYPE_2__*) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StopConnection (TYPE_2__*,int) ; 
 scalar_t__ WaitThread (int /*<<< orphan*/ ,int) ; 

void StopSessionEx(SESSION *s, bool no_wait)
{
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	// Halting flag
	s->UserCanceled = true;
	s->CancelConnect = true;
	s->Halt = true;

	Debug("Stop Session %s\n", s->Name);

	// Cancel
	Cancel(s->Cancel1);

	// Event
	Set(s->HaltEvent);

	// Server and client mode
	if (s->Connection)
	{
		CONNECTION *c = s->Connection;
		AddRef(c->ref);
		StopConnection(c, no_wait);
		ReleaseConnection(c);
	}

	// Wait until the stop
	if (no_wait == false)
	{
		while (true)
		{
			s->ForceStopFlag = true;
			s->Halt = true;
			if (WaitThread(s->Thread, 20))
			{
				break;
			}
		}
	}
	else
	{
		s->ForceStopFlag = true;
		s->Halt = true;
	}
}