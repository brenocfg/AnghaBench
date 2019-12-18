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
struct TYPE_3__ {int Halt; } ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 scalar_t__ MsGetProcessId () ; 
 scalar_t__ PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  StopListener (TYPE_1__*) ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 TYPE_1__* cn_listener ; 
 int /*<<< orphan*/  cn_listener_lock ; 
 scalar_t__ cn_next_allow ; 

void CnReleaseSocket(SOCK *s, PACK *p)
{
	UINT pid = 0;
	UINT current_pid = 0;
	// Validate arguments
	if (s == NULL || p == NULL)
	{
		return;
	}

	pid = PackGetInt(p, "pid");

#ifdef	OS_WIN32
	current_pid = MsGetProcessId();
#endif	// OS_WIN32

	if (current_pid == pid)
	{
		return;
	}

	Lock(cn_listener_lock);
	{
		if (cn_listener != NULL)
		{
			if (cn_listener->Halt == false)
			{
				StopListener(cn_listener);

				cn_next_allow = Tick64() + (6 * 1000);
			}
		}
	}
	Unlock(cn_listener_lock);
}