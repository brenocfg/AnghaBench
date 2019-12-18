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
typedef  int u32 ;
struct TYPE_2__ {int poll; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI_TransferCommands () ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 int* _siReg ; 
 TYPE_1__ sicntrl ; 

void SI_EnablePolling(u32 poll)
{
	u32 level,mask;
	_CPU_ISR_Disable(level);
	poll >>= 24;
	mask = (poll>>4)&0x0f;
	sicntrl.poll &= ~mask;

	poll &= (0x03fffff0|mask);

	sicntrl.poll |= (poll&~0x03ffff00);
	SI_TransferCommands();
	_siReg[12] = sicntrl.poll;
	_CPU_ISR_Restore(level);
}