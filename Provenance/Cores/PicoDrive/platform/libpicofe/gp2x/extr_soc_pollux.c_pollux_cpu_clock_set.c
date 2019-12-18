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
 int /*<<< orphan*/  cpu_clock_allowed ; 
 int* memregl ; 
 int pollux_cpu_clock_get () ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

int pollux_cpu_clock_set(int mhz)
{
	int adiv, mdiv, pdiv, sdiv = 0;
	int i, vf000, vf004;

	if (!cpu_clock_allowed)
		return -1;
	if (mhz == pollux_cpu_clock_get())
		return 0;

	// m = MDIV, p = PDIV, s = SDIV
	#define SYS_CLK_FREQ 27
	pdiv = 9;
	mdiv = (mhz * pdiv) / SYS_CLK_FREQ;
	if (mdiv & ~0x3ff)
		return -1;
	vf004 = (pdiv<<18) | (mdiv<<8) | sdiv;

	// attempt to keep the AHB divider close to 250, but not higher
	for (adiv = 1; mhz / adiv > 250; adiv++)
		;

	vf000 = memregl[0xf000>>2];
	vf000 = (vf000 & ~0x3c0) | ((adiv - 1) << 6);
	memregl[0xf000>>2] = vf000;
	memregl[0xf004>>2] = vf004;
	memregl[0xf07c>>2] |= 0x8000;
	for (i = 0; (memregl[0xf07c>>2] & 0x8000) && i < 0x100000; i++)
		;

	printf("clock set to %dMHz, AHB set to %dMHz\n", mhz, mhz / adiv);
	return 0;
}