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
struct TYPE_2__ {scalar_t__ Opened; int /*<<< orphan*/ * Event; } ;
typedef  int /*<<< orphan*/  NEO_EVENT ;
typedef  int /*<<< orphan*/  IRP ;
typedef  int /*<<< orphan*/  IO_STACK_LOCATION ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  NeoClearPacketQueue (int) ; 
 int /*<<< orphan*/  NeoFreeEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NeoLockPacketQueue () ; 
 int /*<<< orphan*/  NeoSetConnectState (scalar_t__) ; 
 int /*<<< orphan*/  NeoUnlockPacketQueue () ; 
 scalar_t__ TRUE ; 
 TYPE_1__* ctx ; 

BOOL NeoNdisOnClose(IRP *irp, IO_STACK_LOCATION *stack)
{
	NEO_EVENT *free_event = NULL;
	if (ctx == NULL)
	{
		return FALSE;
	}

	if (ctx->Opened == FALSE)
	{
		// Client is not connected
		return FALSE;
	}
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
		NeoFreeEvent(free_event);
	}

	NeoSetConnectState(FALSE);

	return TRUE;
}