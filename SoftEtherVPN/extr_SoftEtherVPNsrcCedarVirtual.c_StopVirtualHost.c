#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* Session; } ;
typedef  TYPE_1__ VH ;
struct TYPE_9__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_2__ SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockVirtual (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseSession (TYPE_2__*) ; 
 int /*<<< orphan*/  StopSession (TYPE_2__*) ; 
 int /*<<< orphan*/  UnlockVirtual (TYPE_1__*) ; 

void StopVirtualHost(VH *v)
{
	SESSION *s;
	// Validate arguments
	if (v == NULL)
	{
		return;
	}

	// Get the session corresponding to the virtual host
	LockVirtual(v);
	{
		s = v->Session;
		if (s != NULL)
		{
			AddRef(s->ref);
		}
	}
	UnlockVirtual(v);

	if (s == NULL)
	{
		// This session is already stopped
		return;
	}

	// Stop Session
	StopSession(s);

	ReleaseSession(s);
}