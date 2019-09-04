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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  KDBG_FLAG_FILTERED ; 
 int /*<<< orphan*/  kernel_debug_flags (int /*<<< orphan*/ ,uintptr_t,uintptr_t,uintptr_t,uintptr_t,int /*<<< orphan*/ ) ; 

void
kernel_debug_filtered(
	uint32_t debugid,
	uintptr_t arg1,
	uintptr_t arg2,
	uintptr_t arg3,
	uintptr_t arg4)
{
	kernel_debug_flags(debugid, arg1, arg2, arg3, arg4, KDBG_FLAG_FILTERED);
}