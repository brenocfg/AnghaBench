#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_5__ {scalar_t__ MaxLoggedPacketsPerMinuteStartTick; scalar_t__ CurrentNumPackets; scalar_t__ L3SwitchMode; scalar_t__ LinkModeClient; scalar_t__ LinkModeServer; scalar_t__ BridgeMode; scalar_t__ SecureNATMode; TYPE_1__* Policy; } ;
struct TYPE_4__ {scalar_t__ NoBroadcastLimiter; } ;
typedef  TYPE_2__ SESSION ;

/* Variables and functions */

bool CheckMaxLoggedPacketsPerMinute(SESSION *s, UINT max_packets, UINT64 now)
{
	UINT64 minute = 60 * 1000;
	// Validate arguments
	if (s == NULL || max_packets == 0)
	{
		return true;
	}

	if ((s->Policy != NULL && s->Policy->NoBroadcastLimiter) ||
		s->SecureNATMode || s->BridgeMode || s->LinkModeServer || s->LinkModeClient ||
		s->L3SwitchMode)
	{
		return true;
	}

	if (s->MaxLoggedPacketsPerMinuteStartTick == 0 ||
		((s->MaxLoggedPacketsPerMinuteStartTick + minute) <= now))
	{
		s->MaxLoggedPacketsPerMinuteStartTick = now;
		s->CurrentNumPackets = 0;
	}

	s->CurrentNumPackets++;
	if (s->CurrentNumPackets > max_packets)
	{
		return false;
	}

	return true;
}