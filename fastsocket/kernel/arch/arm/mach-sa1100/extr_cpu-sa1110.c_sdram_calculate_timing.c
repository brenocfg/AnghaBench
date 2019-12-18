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
typedef  int u_int ;
struct sdram_params {int cas_latency; int /*<<< orphan*/  trcd; int /*<<< orphan*/  trp; int /*<<< orphan*/  twr; int /*<<< orphan*/  tck; } ;
struct sdram_info {int mdcnfg; int mdrefr; int /*<<< orphan*/ * mdcas; } ;

/* Variables and functions */
 scalar_t__ CPU_REVISION ; 
 scalar_t__ CPU_SA1110_B2 ; 
 int MDCNFG ; 
 int MDREFR ; 
 int MDREFR_K1DB2 ; 
 int ns_to_cycles (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mdcas (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
sdram_calculate_timing(struct sdram_info *sd, u_int cpu_khz,
		       struct sdram_params *sdram)
{
	u_int mem_khz, sd_khz, trp, twr;

	mem_khz = cpu_khz / 2;
	sd_khz = mem_khz;

	/*
	 * If SDCLK would invalidate the SDRAM timings,
	 * run SDCLK at half speed.
	 *
	 * CPU steppings prior to B2 must either run the memory at
	 * half speed or use delayed read latching (errata 13).
	 */
	if ((ns_to_cycles(sdram->tck, sd_khz) > 1) ||
	    (CPU_REVISION < CPU_SA1110_B2 && sd_khz < 62000))
		sd_khz /= 2;

	sd->mdcnfg = MDCNFG & 0x007f007f;

	twr = ns_to_cycles(sdram->twr, mem_khz);

	/* trp should always be >1 */
	trp = ns_to_cycles(sdram->trp, mem_khz) - 1;
	if (trp < 1)
		trp = 1;

	sd->mdcnfg |= trp << 8;
	sd->mdcnfg |= trp << 24;
	sd->mdcnfg |= sdram->cas_latency << 12;
	sd->mdcnfg |= sdram->cas_latency << 28;
	sd->mdcnfg |= twr << 14;
	sd->mdcnfg |= twr << 30;

	sd->mdrefr = MDREFR & 0xffbffff0;
	sd->mdrefr |= 7;

	if (sd_khz != mem_khz)
		sd->mdrefr |= MDREFR_K1DB2;

	/* initial number of '1's in MDCAS + 1 */
	set_mdcas(sd->mdcas, sd_khz >= 62000, ns_to_cycles(sdram->trcd, mem_khz));

#ifdef DEBUG
	printk("MDCNFG: %08x MDREFR: %08x MDCAS0: %08x MDCAS1: %08x MDCAS2: %08x\n",
		sd->mdcnfg, sd->mdrefr, sd->mdcas[0], sd->mdcas[1], sd->mdcas[2]);
#endif
}