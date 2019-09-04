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
struct TYPE_2__ {scalar_t__ Opened; int /*<<< orphan*/ * Event; int /*<<< orphan*/  HardwareID; } ;
typedef  int /*<<< orphan*/  IRP ;
typedef  int /*<<< orphan*/  IO_STACK_LOCATION ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int MAX_SIZE ; 
 char* NDIS_NEO_EVENT_NAME ; 
 int /*<<< orphan*/ * NeoNewEvent (char*) ; 
 int /*<<< orphan*/  NeoSetConnectState (scalar_t__) ; 
 scalar_t__ TRUE ; 
 TYPE_1__* ctx ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

BOOL NeoNdisOnOpen(IRP *irp, IO_STACK_LOCATION *stack)
{
	char name[MAX_SIZE];

	if (ctx == NULL)
	{
		return FALSE;
	}

	if (ctx->Opened != FALSE)
	{
		// Another client is connected already
		return FALSE;
	}
	ctx->Opened = TRUE;

	// Initialize the event name
	sprintf(name, NDIS_NEO_EVENT_NAME, ctx->HardwareID);

	// Register a Event
#ifndef	WIN9X
	ctx->Event = NeoNewEvent(name);
	if (ctx->Event == NULL)
	{
		ctx->Opened = FALSE;
		return FALSE;
	}
#endif	// WIN9X

	// Set the connection state
	NeoSetConnectState(TRUE);

	return TRUE;
}