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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ cpu_khz ; 
 int /*<<< orphan*/  do_div (int,unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*,int) ; 
 int /*<<< orphan*/  wrmsr (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_watchdog_counter32(unsigned int perfctr_msr,
				const char *descr, unsigned nmi_hz)
{
	u64 count = (u64)cpu_khz * 1000;

	do_div(count, nmi_hz);
	if (descr)
		pr_debug("setting %s to -0x%08Lx\n", descr, count);
	wrmsr(perfctr_msr, (u32)(-count), 0);
}