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
typedef  scalar_t__ UINT64 ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  EVENT ;

/* Variables and functions */
 int GetHostIPAddressHash32 () ; 
 scalar_t__ IsRouteChanged (void*) ; 
 int MIN (int,int) ; 
 scalar_t__ Tick64 () ; 
 scalar_t__ Wait (int /*<<< orphan*/ *,int) ; 

void WaitUntilHostIPAddressChanged(void *p, EVENT *event, UINT timeout, UINT ip_check_interval)
{
	UINT64 start, end;
	UINT last_hash;
	// Validate arguments
	if (timeout == 0x7FFFFFFF)
	{
		timeout = 0xFFFFFFFF;
	}
	if (ip_check_interval == 0)
	{
		ip_check_interval = 0xFFFFFFFF;
	}
	if (event == NULL || timeout == 0)
	{
		return;
	}

	start = Tick64();
	end = start + (UINT64)timeout;
	last_hash = GetHostIPAddressHash32();

	while (true)
	{
		UINT64 now = Tick64();
		UINT next_interval;

		if (now >= end)
		{
			break;
		}

		if (p != NULL)
		{
			if (IsRouteChanged(p))
			{
				break;
			}
		}

		if (last_hash != GetHostIPAddressHash32())
		{
			break;
		}

		next_interval = (UINT)(end - now);
		next_interval = MIN(next_interval, ip_check_interval);

		if (Wait(event, next_interval))
		{
			break;
		}
	}
}