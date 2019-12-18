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

/* Variables and functions */

__attribute__((used)) static void gdbstub_load_fpu(void)
{
#ifdef CONFIG_FPU

	asm volatile(
		"or %1,epsw\n"
#ifdef CONFIG_MN10300_PROC_MN103E010
		"nop\n"
		"nop\n"
#endif
		"mov %0, a1\n"
		"fmov (a1+), fs0\n"
		"fmov (a1+), fs1\n"
		"fmov (a1+), fs2\n"
		"fmov (a1+), fs3\n"
		"fmov (a1+), fs4\n"
		"fmov (a1+), fs5\n"
		"fmov (a1+), fs6\n"
		"fmov (a1+), fs7\n"
		"fmov (a1+), fs8\n"
		"fmov (a1+), fs9\n"
		"fmov (a1+), fs10\n"
		"fmov (a1+), fs11\n"
		"fmov (a1+), fs12\n"
		"fmov (a1+), fs13\n"
		"fmov (a1+), fs14\n"
		"fmov (a1+), fs15\n"
		"fmov (a1+), fs16\n"
		"fmov (a1+), fs17\n"
		"fmov (a1+), fs18\n"
		"fmov (a1+), fs19\n"
		"fmov (a1+), fs20\n"
		"fmov (a1+), fs21\n"
		"fmov (a1+), fs22\n"
		"fmov (a1+), fs23\n"
		"fmov (a1+), fs24\n"
		"fmov (a1+), fs25\n"
		"fmov (a1+), fs26\n"
		"fmov (a1+), fs27\n"
		"fmov (a1+), fs28\n"
		"fmov (a1+), fs29\n"
		"fmov (a1+), fs30\n"
		"fmov (a1+), fs31\n"
		"fmov %2, fpcr\n"
		:
		: "g" (&gdbstub_fpufs_array), "i"(EPSW_FE), "d"(gdbstub_fpcr)
		: "a1"
	);
#endif
}