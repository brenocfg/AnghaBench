#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  PAD_ENABLEDMASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_DisablePolling (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_SetWirelessID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pad_checkingbits ; 
 int /*<<< orphan*/  __pad_enabledbits ; 
 int /*<<< orphan*/  __pad_pendingbits ; 
 int /*<<< orphan*/  __pad_waitingbits ; 

__attribute__((used)) static void __pad_disable(u32 chan)
{
	u32 level,mask;
	_CPU_ISR_Disable(level);
	mask = PAD_ENABLEDMASK(chan);
	SI_DisablePolling(mask);
	__pad_enabledbits &= ~mask;
	__pad_waitingbits &= ~mask;
	__pad_pendingbits &= ~mask;
	__pad_checkingbits &= ~mask;
	SYS_SetWirelessID(chan,0);
	_CPU_ISR_Restore(level);
}