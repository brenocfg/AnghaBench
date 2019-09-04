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
struct TYPE_3__ {int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ NEO_EVENT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KeSetEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void NeoSet(NEO_EVENT *event)
{
	// Validate arguments
	if (event == NULL)
	{
		return;
	}

#ifndef	WIN9X
	KeSetEvent(event->event, 0, FALSE);
#else	// WIN9X
	if (event->win32_event != 0)
	{
		DWORD h = event->win32_event;
		_asm mov eax, h;
		VxDCall(_VWIN32_SetWin32Event);
	}
#endif	// WIN9X
}