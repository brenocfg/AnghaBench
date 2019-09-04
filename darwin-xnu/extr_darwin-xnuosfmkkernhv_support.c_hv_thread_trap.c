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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  HV_THREAD_TRAP ; 
 int /*<<< orphan*/  HV_TRAP_DISPATCH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_get_thread_target () ; 

kern_return_t hv_thread_trap(uint64_t index, uint64_t arg) {
	return HV_TRAP_DISPATCH(HV_THREAD_TRAP, index, hv_get_thread_target(), arg);
}