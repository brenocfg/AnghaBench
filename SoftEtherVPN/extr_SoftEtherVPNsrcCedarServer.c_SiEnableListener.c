#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int /*<<< orphan*/  DisableDos; } ;
struct TYPE_8__ {int /*<<< orphan*/  Cedar; } ;
struct TYPE_7__ {int Enabled; int /*<<< orphan*/  DisableDos; TYPE_6__* Listener; int /*<<< orphan*/  Port; } ;
typedef  TYPE_1__ SERVER_LISTENER ;
typedef  TYPE_2__ SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  LISTENER_TCP ; 
 TYPE_6__* NewListener (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* SiGetListener (TYPE_2__*,scalar_t__) ; 

bool SiEnableListener(SERVER *s, UINT port)
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

	if (e->Enabled)
	{
		// It has already started
		return true;
	}

	// Create a listener
	e->Listener = NewListener(s->Cedar, LISTENER_TCP, e->Port);
	if (e->Listener == NULL)
	{
		// Failure
		return false;
	}

	e->Listener->DisableDos = e->DisableDos;

	e->Enabled = true;

	return true;
}