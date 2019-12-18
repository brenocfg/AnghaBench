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
 int SYS_CLK_FREQ ; 
 int cpu_current_mhz ; 
 int cpuclk_was_changed ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int* memregs ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int mmsp2_clock_set(int mhz)
{
	unsigned int mdiv, pdiv, sdiv = 0;
	unsigned int v;
	int i;

	pdiv = 3;
	mdiv = (mhz * pdiv * 1000000) / SYS_CLK_FREQ;
	if (mdiv & ~0xff) {
		fprintf(stderr, "invalid cpuclk MHz: %u\n", mhz);
		return -1;
	}
	v = ((mdiv-8)<<8) | ((pdiv-2)<<2) | sdiv;
	memregs[0x910>>1] = v;

	for (i = 0; i < 10000; i++)
		if (!(memregs[0x902>>1] & 1))
			break;

	cpuclk_was_changed = 1;
	cpu_current_mhz = mhz;
	return 0;
}