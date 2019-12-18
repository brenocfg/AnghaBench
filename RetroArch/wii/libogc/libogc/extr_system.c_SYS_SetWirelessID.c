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
typedef  size_t u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_3__ {scalar_t__* wirelessPad_id; } ;
typedef  TYPE_1__ syssramex ;

/* Variables and functions */
 TYPE_1__* __SYS_LockSramEx () ; 
 int /*<<< orphan*/  __SYS_UnlockSramEx (size_t) ; 

void SYS_SetWirelessID(u32 chan,u32 id)
{
	u32 write;
	syssramex *sram;

	write = 0;
	sram = __SYS_LockSramEx();
	if(sram->wirelessPad_id[chan]!=(u16)id) {
		sram->wirelessPad_id[chan] = (u16)id;
		write = 1;
	}
	__SYS_UnlockSramEx(write);
}