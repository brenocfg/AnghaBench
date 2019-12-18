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
typedef  int s32 ;
typedef  int /*<<< orphan*/  dvdcbcallback ;

/* Variables and functions */
 int /*<<< orphan*/  DVD_Pause () ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 

s32 DVD_CancelAllAsync(dvdcbcallback cb)
{
	u32 level;
	_CPU_ISR_Disable(level);
	DVD_Pause();
	_CPU_ISR_Restore(level);
	return 1;
}