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
typedef  scalar_t__ UINT64 ;
struct TYPE_3__ {int Inited; scalar_t__ YourPort; scalar_t__ LastRecvTick; scalar_t__ Now; scalar_t__ FirstStableReceiveTick; scalar_t__ FastDetect; int /*<<< orphan*/  YourIp; } ;
typedef  TYPE_1__ UDP_ACCEL ;

/* Variables and functions */
 scalar_t__ IsZeroIp (int /*<<< orphan*/ *) ; 
 scalar_t__ UDP_ACCELERATION_KEEPALIVE_TIMEOUT ; 
 scalar_t__ UDP_ACCELERATION_KEEPALIVE_TIMEOUT_FAST ; 
 scalar_t__ UDP_ACCELERATION_REQUIRE_CONTINUOUS ; 

bool UdpAccelIsSendReady(UDP_ACCEL *a, bool check_keepalive)
{
	UINT64 timeout_value;
	// Validate arguments
	if (a == NULL)
	{
		return false;
	}

	if (a->Inited == false)
	{
		return false;
	}

	if (a->YourPort == 0)
	{
		return false;
	}

	if (IsZeroIp(&a->YourIp))
	{
		return false;
	}

	timeout_value = UDP_ACCELERATION_KEEPALIVE_TIMEOUT;

	if (a->FastDetect)
	{
		timeout_value = UDP_ACCELERATION_KEEPALIVE_TIMEOUT_FAST;
	}

	if (check_keepalive)
	{
		if (a->LastRecvTick == 0 || ((a->LastRecvTick + timeout_value) < a->Now))
		{
			a->FirstStableReceiveTick = 0;
			return false;
		}
		else
		{
			if ((a->FirstStableReceiveTick + (UINT64)UDP_ACCELERATION_REQUIRE_CONTINUOUS) <= a->Now)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	return true;
}