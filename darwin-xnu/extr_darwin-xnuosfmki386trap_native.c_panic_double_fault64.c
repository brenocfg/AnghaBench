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
typedef  int /*<<< orphan*/  x86_saved_state_t ;
typedef  int /*<<< orphan*/  UInt32 ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OSCompareAndSwap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  volatile*) ; 
 int /*<<< orphan*/  PANIC_DOUBLE_FAULT ; 
 scalar_t__ cpu_number () ; 
 int /*<<< orphan*/  panic_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic_double_fault_cpu ; 

void
panic_double_fault64(x86_saved_state_t *sp)
{
	(void)OSCompareAndSwap((UInt32) -1, (UInt32) cpu_number(), (volatile UInt32 *)&panic_double_fault_cpu);
	panic_64(sp, PANIC_DOUBLE_FAULT, "Double fault", FALSE);

}