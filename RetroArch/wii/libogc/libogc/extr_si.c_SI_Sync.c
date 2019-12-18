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
 int SICOMCSR_TSTART ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __si_completetransfer () ; 
 int /*<<< orphan*/  __si_transfernext (int) ; 
 int* _siReg ; 

u32 SI_Sync()
{
	u32 level,ret;

	while(_siReg[13]&SICOMCSR_TSTART);

	_CPU_ISR_Disable(level);
	ret = __si_completetransfer();
	__si_transfernext(4);
	_CPU_ISR_Restore(level);

	return ret;
}