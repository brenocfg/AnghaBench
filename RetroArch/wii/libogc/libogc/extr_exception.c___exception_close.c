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
typedef  size_t u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DCFlushRangeNoSync (void*,int) ; 
 int /*<<< orphan*/  ICInvalidateRange (void*,int) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (size_t) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (size_t) ; 
 int /*<<< orphan*/  __exception_sethandler (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _sync () ; 
 int* exception_location ; 

void __exception_close(u32 except)
{
	u32 level;
	void *pAdd = (void*)(0x80000000|exception_location[except]);

	_CPU_ISR_Disable(level);
	__exception_sethandler(except,NULL);

	*(u32*)pAdd = 0x4C000064;
	DCFlushRangeNoSync(pAdd,0x100);
	ICInvalidateRange(pAdd,0x100);
	_sync();
	_CPU_ISR_Restore(level);
}