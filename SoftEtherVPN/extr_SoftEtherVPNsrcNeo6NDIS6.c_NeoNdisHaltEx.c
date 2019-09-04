#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_2__ {scalar_t__ Halting; scalar_t__ NumCurrentDispatch; scalar_t__ ConnectedOld; scalar_t__ ConnectedForce; scalar_t__ Connected; scalar_t__ Inited; scalar_t__ Initing; int /*<<< orphan*/ * Event; scalar_t__ Opened; } ;
typedef  int /*<<< orphan*/  NEO_EVENT ;
typedef  int /*<<< orphan*/  NDIS_HANDLE ;
typedef  int /*<<< orphan*/  NDIS_HALT_ACTION ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  NdisMSleep (int) ; 
 int /*<<< orphan*/  NeoClearPacketQueue (int) ; 
 int /*<<< orphan*/  NeoFreeControlDevice () ; 
 int /*<<< orphan*/  NeoFreeEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NeoFreePacketArray () ; 
 int /*<<< orphan*/  NeoLockPacketQueue () ; 
 int /*<<< orphan*/  NeoSet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NeoShutdown () ; 
 int /*<<< orphan*/  NeoStopAdapter () ; 
 int /*<<< orphan*/  NeoUnlockPacketQueue () ; 
 scalar_t__ TRUE ; 
 TYPE_1__* ctx ; 

void NeoNdisHaltEx(NDIS_HANDLE MiniportAdapterContext, NDIS_HALT_ACTION HaltAction)
{
	NEO_EVENT *free_event = NULL;
	UINT counter_dbg = 0;
	if (ctx == NULL)
	{
		return;
	}

	if (ctx->Halting != FALSE)
	{
		// That has already been stopped
		return;
	}
	ctx->Halting = TRUE;

	ctx->Opened = FALSE;

	NeoLockPacketQueue();
	{
		// Release the event
		free_event = ctx->Event;
		ctx->Event = NULL;

		// Release all packets
		NeoClearPacketQueue(true);
	}
	NeoUnlockPacketQueue();

	if (free_event != NULL)
	{
		NeoSet(free_event);
	}

	// Wait for complete all tasks
	while (ctx->NumCurrentDispatch != 0)
	{
		NdisMSleep(10000);
		counter_dbg++;
		if (counter_dbg >= 1500)
		{
			break;
		}
	}

	if (free_event != NULL)
	{
		NeoFreeEvent(free_event);
	}

	// Delete the control device
	NeoFreeControlDevice();

	// Stop the adapter
	NeoStopAdapter();

	// Release the packet array
	NeoFreePacketArray();

	// Complete to stop
	ctx->Initing = ctx->Inited = FALSE;
	ctx->Connected = ctx->ConnectedForce = ctx->ConnectedOld = FALSE;
	ctx->Halting = FALSE;

	// Shutdown of Neo
	NeoShutdown();
}