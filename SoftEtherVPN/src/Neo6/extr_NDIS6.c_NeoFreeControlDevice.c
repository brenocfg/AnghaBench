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
struct TYPE_2__ {scalar_t__ Opened; int /*<<< orphan*/  NdisControl; int /*<<< orphan*/ * Event; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  NdisDeregisterDeviceEx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NeoFreeEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NeoSet (int /*<<< orphan*/ *) ; 
 TYPE_1__* ctx ; 

void NeoFreeControlDevice()
{
	if (ctx == NULL)
	{
		return;
	}

	if (ctx->Opened != FALSE)
	{
		// Delete the event
		NeoSet(ctx->Event);
		NeoFreeEvent(ctx->Event);
		ctx->Event = NULL;
		ctx->Opened = FALSE;
	}

	// Delete the device
	NdisDeregisterDeviceEx(ctx->NdisControl);
}