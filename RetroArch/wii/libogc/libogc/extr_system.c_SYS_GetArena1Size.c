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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  _CPU_ISR_Disable (scalar_t__) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (scalar_t__) ; 
 scalar_t__ __sysarena1hi ; 
 scalar_t__ __sysarena1lo ; 

u32 SYS_GetArena1Size()
{
	u32 level,size;

	_CPU_ISR_Disable(level);
	size = ((u32)__sysarena1hi - (u32)__sysarena1lo);
	_CPU_ISR_Restore(level);

	return size;
}