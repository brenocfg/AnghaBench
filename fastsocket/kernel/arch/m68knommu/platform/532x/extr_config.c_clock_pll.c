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
 int BUSDIV ; 
 int /*<<< orphan*/  DEFAULT_LPD ; 
 int FREF ; 
 int MAX_FSYS ; 
 int MCF_PLL_PFDR ; 
 int MCF_PLL_PODR ; 
 int MCF_PLL_PODR_BUSDIV (int) ; 
 int MCF_PLL_PODR_CPUDIV (int) ; 
 int /*<<< orphan*/  MCF_SDRAMC_LIMP_FIX ; 
 int /*<<< orphan*/  MCF_SDRAMC_REFRESH ; 
 int MCF_SDRAMC_SDCR ; 
 int MCF_SDRAMC_SDCR_CKE ; 
 int MCF_SDRAMC_SDCR_REF ; 
 int MIN_FSYS ; 
 int /*<<< orphan*/  clock_exit_limp () ; 
 int /*<<< orphan*/  clock_limp (int /*<<< orphan*/ ) ; 

int clock_pll(int fsys, int flags)
{
	int fref, temp, fout, mfd;
	u32 i;

	fref = FREF;
        
	if (fsys == 0) {
		/* Return current PLL output */
		mfd = MCF_PLL_PFDR;

		return (fref * mfd / (BUSDIV * 4));
	}

	/* Check bounds of requested system clock */
	if (fsys > MAX_FSYS)
		fsys = MAX_FSYS;
	if (fsys < MIN_FSYS)
		fsys = MIN_FSYS;

	/* Multiplying by 100 when calculating the temp value,
	   and then dividing by 100 to calculate the mfd allows
	   for exact values without needing to include floating
	   point libraries. */
	temp = 100 * fsys / fref;
	mfd = 4 * BUSDIV * temp / 100;
    	    	    	
	/* Determine the output frequency for selected values */
	fout = (fref * mfd / (BUSDIV * 4));

	/*
	 * Check to see if the SDRAM has already been initialized.
	 * If it has then the SDRAM needs to be put into self refresh
	 * mode before reprogramming the PLL.
	 */
	if (MCF_SDRAMC_SDCR & MCF_SDRAMC_SDCR_REF)
		/* Put SDRAM into self refresh mode */
		MCF_SDRAMC_SDCR &= ~MCF_SDRAMC_SDCR_CKE;

	/*
	 * Initialize the PLL to generate the new system clock frequency.
	 * The device must be put into LIMP mode to reprogram the PLL.
	 */

	/* Enter LIMP mode */
	clock_limp(DEFAULT_LPD);
     					
	/* Reprogram PLL for desired fsys */
	MCF_PLL_PODR = (0
		| MCF_PLL_PODR_CPUDIV(BUSDIV/3)
		| MCF_PLL_PODR_BUSDIV(BUSDIV));
						
	MCF_PLL_PFDR = mfd;
		
	/* Exit LIMP mode */
	clock_exit_limp();
	
	/*
	 * Return the SDRAM to normal operation if it is in use.
	 */
	if (MCF_SDRAMC_SDCR & MCF_SDRAMC_SDCR_REF)
		/* Exit self refresh mode */
		MCF_SDRAMC_SDCR |= MCF_SDRAMC_SDCR_CKE;

	/* Errata - workaround for SDRAM opeartion after exiting LIMP mode */
	MCF_SDRAMC_LIMP_FIX = MCF_SDRAMC_REFRESH;

	/* wait for DQS logic to relock */
	for (i = 0; i < 0x200; i++)
		;

	return fout;
}