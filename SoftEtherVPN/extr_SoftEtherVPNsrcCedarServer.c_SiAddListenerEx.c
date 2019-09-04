#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_10__ {int DisableDos; } ;
struct TYPE_9__ {int /*<<< orphan*/  ServerListenerList; int /*<<< orphan*/  Cedar; } ;
struct TYPE_8__ {scalar_t__ Port; int Enabled; int DisableDos; TYPE_5__* Listener; } ;
typedef  TYPE_1__ SERVER_LISTENER ;
typedef  TYPE_2__ SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  LISTENER_TCP ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 TYPE_5__* NewListener (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* ZeroMalloc (int) ; 

bool SiAddListenerEx(SERVER *s, UINT port, bool enabled, bool disable_dos)
{
	SERVER_LISTENER *e;
	UINT i;
	// Validate arguments
	if (s == NULL || port == 0)
	{
		return false;
	}

	// Check whether the listener exists already
	for (i = 0;i < LIST_NUM(s->ServerListenerList);i++)
	{
		e = LIST_DATA(s->ServerListenerList, i);
		if (e->Port == port)
		{
			// Already exist
			return false;
		}
	}

	// Register by initializing a new listener
	e = ZeroMalloc(sizeof(SERVER_LISTENER));
	e->Enabled = enabled;
	e->Port = port;
	e->DisableDos = disable_dos;

	if (e->Enabled)
	{
		// Create a listener
		e->Listener = NewListener(s->Cedar, LISTENER_TCP, e->Port);
		if (e->Listener != NULL)
		{
			e->Listener->DisableDos = e->DisableDos;
		}
	}

	Insert(s->ServerListenerList, e);

	return true;
}