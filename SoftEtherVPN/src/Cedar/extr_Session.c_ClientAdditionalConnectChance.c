#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
struct TYPE_8__ {int EnableUdpRecovery; scalar_t__ MaxConnection; scalar_t__ NextConnectionTime; TYPE_2__* ClientOption; TYPE_1__* Connection; scalar_t__ Halt; scalar_t__ IsRUDPSession; scalar_t__ ServerMode; } ;
struct TYPE_7__ {scalar_t__ AdditionalConnectionInterval; } ;
struct TYPE_6__ {scalar_t__ Protocol; scalar_t__ AdditionalConnectionFailedCounter; int /*<<< orphan*/  CurrentNumConnection; } ;
typedef  TYPE_3__ SESSION ;

/* Variables and functions */
 scalar_t__ CONNECTION_TCP ; 
 scalar_t__ Count (int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_ADDITIONAL_CONNECTION_FAILED_COUNTER ; 
 int /*<<< orphan*/  SessionAdditionalConnect (TYPE_3__*) ; 
 scalar_t__ Tick64 () ; 

void ClientAdditionalConnectChance(SESSION *s)
{
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	if (s->ServerMode)
	{
		// Do not connect additionally in the server mode
		return;
	}
	if (s->Connection->Protocol != CONNECTION_TCP)
	{
		// Connect additionally only in the case of TCP protocol
		return;
	}
	if (s->IsRUDPSession && s->EnableUdpRecovery == false)
	{
		// Do not connect additionally if the UDP recovery is disabled in the case of R-UDP session
		return;
	}

	if (s->IsRUDPSession && (s->Connection->AdditionalConnectionFailedCounter > MAX_ADDITIONAL_CONNECTION_FAILED_COUNTER))
	{
		// Not to make a large amount of repeated connection retry within a certain time in the case of R-UDP session
		return;
	}

	while (true)
	{
		if (s->Halt)
		{
			return;
		}
		// Consider whether there is a need to put an additional connection
		// by examining the number of current connections and MaxConnection property
		if (Count(s->Connection->CurrentNumConnection) < s->MaxConnection)
		{
			// Get the current time
			UINT64 now = Tick64();

			// Examine the NextConnectionTime, and if the time passed,
			// attempt to make a connection
			if (s->NextConnectionTime == 0 ||
				s->ClientOption->AdditionalConnectionInterval == 0 ||
				(s->NextConnectionTime <= now))
			{
				// Start the work to put an additional connection
				s->NextConnectionTime = now + s->ClientOption->AdditionalConnectionInterval * (UINT64)1000U;
				SessionAdditionalConnect(s);
			}
			else
			{
				break;
			}
		}
		else
		{
			break;
		}
	}
}