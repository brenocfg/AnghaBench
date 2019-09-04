#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  event_handle; } ;
typedef  TYPE_1__ NEO_EVENT ;

/* Variables and functions */
 int /*<<< orphan*/  NeoFree (TYPE_1__*) ; 
 int /*<<< orphan*/  ZwClose (int /*<<< orphan*/ ) ; 

void NeoFreeEvent(NEO_EVENT *event)
{
	// Validate arguments
	if (event == NULL)
	{
		return;
	}

	ZwClose(event->event_handle);

	// Release the memory
	NeoFree(event);
}