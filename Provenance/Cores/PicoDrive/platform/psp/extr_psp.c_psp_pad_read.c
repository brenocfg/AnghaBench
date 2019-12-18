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
struct TYPE_4__ {unsigned int Buttons; int Lx; int Ly; } ;
typedef  TYPE_1__ SceCtrlData ;

/* Variables and functions */
 int ANALOG_DEADZONE ; 
 unsigned int PBTN_NUB_DOWN ; 
 unsigned int PBTN_NUB_LEFT ; 
 unsigned int PBTN_NUB_RIGHT ; 
 unsigned int PBTN_NUB_UP ; 
 int /*<<< orphan*/  sceCtrlPeekBufferPositive (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sceCtrlReadBufferPositive (TYPE_1__*,int) ; 

unsigned int psp_pad_read(int blocking)
{
	unsigned int buttons;
	SceCtrlData pad;
	if (blocking)
	     sceCtrlReadBufferPositive(&pad, 1);
	else sceCtrlPeekBufferPositive(&pad, 1);
	buttons = pad.Buttons;

	// analog..
	buttons &= ~(PBTN_NUB_UP|PBTN_NUB_DOWN|PBTN_NUB_LEFT|PBTN_NUB_RIGHT);
	if (pad.Lx < 128 - ANALOG_DEADZONE) buttons |= PBTN_NUB_LEFT;
	if (pad.Lx > 128 + ANALOG_DEADZONE) buttons |= PBTN_NUB_RIGHT;
	if (pad.Ly < 128 - ANALOG_DEADZONE) buttons |= PBTN_NUB_UP;
	if (pad.Ly > 128 + ANALOG_DEADZONE) buttons |= PBTN_NUB_DOWN;

	return buttons;
}