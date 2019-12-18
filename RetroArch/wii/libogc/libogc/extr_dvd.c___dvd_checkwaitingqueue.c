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
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 int /*<<< orphan*/ * __dvd_waitingqueue ; 
 int /*<<< orphan*/  __lwp_queue_isempty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32 __dvd_checkwaitingqueue()
{
	u32 i;
	u32 level;

	_CPU_ISR_Disable(level);
	for(i=0;i<4;i++) {
		if(!__lwp_queue_isempty(&__dvd_waitingqueue[i])) break;
	}
	_CPU_ISR_Restore(level);
	return (i<4);
}