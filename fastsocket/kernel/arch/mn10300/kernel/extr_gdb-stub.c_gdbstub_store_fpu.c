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

__attribute__((used)) static void gdbstub_store_fpu(void)
{
#ifdef CONFIG_FPU

	asm volatile(
		"or %2,epsw\n"
#ifdef CONFIG_MN10300_PROC_MN103E010
		"nop\n"
		"nop\n"
#endif
		"mov %1, a1\n"
		"fmov fs0,  (a1+)\n"
		"fmov fs1,  (a1+)\n"
		"fmov fs2,  (a1+)\n"
		"fmov fs3,  (a1+)\n"
		"fmov fs4,  (a1+)\n"
		"fmov fs5,  (a1+)\n"
		"fmov fs6,  (a1+)\n"
		"fmov fs7,  (a1+)\n"
		"fmov fs8,  (a1+)\n"
		"fmov fs9,  (a1+)\n"
		"fmov fs10, (a1+)\n"
		"fmov fs11, (a1+)\n"
		"fmov fs12, (a1+)\n"
		"fmov fs13, (a1+)\n"
		"fmov fs14, (a1+)\n"
		"fmov fs15, (a1+)\n"
		"fmov fs16, (a1+)\n"
		"fmov fs17, (a1+)\n"
		"fmov fs18, (a1+)\n"
		"fmov fs19, (a1+)\n"
		"fmov fs20, (a1+)\n"
		"fmov fs21, (a1+)\n"
		"fmov fs22, (a1+)\n"
		"fmov fs23, (a1+)\n"
		"fmov fs24, (a1+)\n"
		"fmov fs25, (a1+)\n"
		"fmov fs26, (a1+)\n"
		"fmov fs27, (a1+)\n"
		"fmov fs28, (a1+)\n"
		"fmov fs29, (a1+)\n"
		"fmov fs30, (a1+)\n"
		"fmov fs31, (a1+)\n"
		"fmov fpcr, %0\n"
		: "=d"(gdbstub_fpcr)
		: "g" (&gdbstub_fpufs_array), "i"(EPSW_FE)
		: "a1"
		);
#endif
}