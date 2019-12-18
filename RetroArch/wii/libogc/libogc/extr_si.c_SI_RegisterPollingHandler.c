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
typedef  int u32 ;
typedef  int /*<<< orphan*/ * RDSTHandler ;

/* Variables and functions */
 int /*<<< orphan*/  SI_EnablePollingInterrupt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 int /*<<< orphan*/ ** rdstHandlers ; 

u32 SI_RegisterPollingHandler(RDSTHandler handler)
{
	u32 level,i;

	_CPU_ISR_Disable(level);

	i = 0;
	for(i=0;i<4;i++) {
		if(rdstHandlers[i]==handler) {
			_CPU_ISR_Restore(level);
			return 1;
		}
	}

	for(i=0;i<4;i++) {
		if(rdstHandlers[i]==NULL) {
			rdstHandlers[i] = handler;
			SI_EnablePollingInterrupt(TRUE);
			_CPU_ISR_Restore(level);
			return 1;
		}
	}

	_CPU_ISR_Restore(level);
	return 0;
}