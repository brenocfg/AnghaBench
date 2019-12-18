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
struct TYPE_4__ {struct TYPE_4__* FirmwareVersion; struct TYPE_4__* HardwareVersion; struct TYPE_4__* SerialNumber; struct TYPE_4__* Model; struct TYPE_4__* ManufacturerId; struct TYPE_4__* Label; } ;
typedef  TYPE_1__ SEC_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 

void FreeSecInfoMemory(SEC_INFO *s)
{
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	Free(s->Label);
	Free(s->ManufacturerId);
	Free(s->Model);
	Free(s->SerialNumber);
	Free(s->HardwareVersion);
	Free(s->FirmwareVersion);
	Free(s);
}