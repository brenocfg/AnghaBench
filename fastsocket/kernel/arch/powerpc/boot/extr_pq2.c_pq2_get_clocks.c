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
typedef  int u32 ;

/* Variables and functions */
 size_t PQ2_SCCR ; 
 size_t PQ2_SCMR ; 
 int* fsl_get_immr () ; 
 int in_be32 (int*) ; 
 int* pq2_corecnf_map ; 
 int /*<<< orphan*/  printf (char*) ; 

int pq2_get_clocks(u32 crystal, u32 *sysfreq, u32 *corefreq,
                   u32 *timebase, u32 *brgfreq)
{
	u32 *immr;
	u32 sccr, scmr, mainclk, busclk;
	int corecnf, busdf, plldf, pllmf, dfbrg;

	immr = fsl_get_immr();
	if (!immr) {
		printf("pq2_get_clocks: Couldn't get IMMR base.\r\n");
		return 0;
	}

	sccr = in_be32(&immr[PQ2_SCCR]);
	scmr = in_be32(&immr[PQ2_SCMR]);

	dfbrg = sccr & 3;
	corecnf = (scmr >> 24) & 0x1f;
	busdf = (scmr >> 20) & 0xf;
	plldf = (scmr >> 12) & 1;
	pllmf = scmr & 0xfff;

	mainclk = crystal * (pllmf + 1) / (plldf + 1);
	busclk = mainclk / (busdf + 1);

	if (sysfreq)
		*sysfreq = mainclk / 2;
	if (timebase)
		*timebase = busclk / 4;
	if (brgfreq)
		*brgfreq = mainclk / (1 << ((dfbrg + 1) * 2));

	if (corefreq) {
		int coremult = pq2_corecnf_map[corecnf];

		if (coremult < 0)
			*corefreq = mainclk / 2;
		else if (coremult == 0)
			return 0;
		else
			*corefreq = busclk * coremult / 2;
	}

	return 1;
}