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
 scalar_t__* __ARBlockLen ; 
 int /*<<< orphan*/  __ARFreeBlocks ; 
 scalar_t__ __ARStackPointer ; 

u32 AR_Free(u32 *len)
{
	u32 level;

	_CPU_ISR_Disable(level);
	__ARBlockLen--;
	if(len) *len = *__ARBlockLen;
	__ARStackPointer -= *__ARBlockLen;
	__ARFreeBlocks++;
	_CPU_ISR_Restore(level);

	return __ARStackPointer;
}