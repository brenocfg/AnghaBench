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
typedef  scalar_t__ SDRAM_TRP ;
typedef  scalar_t__ SDRAM_TRCD ;

/* Variables and functions */
 int MCF_SDRAMC_SDCFG1 ; 
 int MCF_SDRAMC_SDCFG1_ACT2RW (int) ; 
 int MCF_SDRAMC_SDCFG1_PRE2ACT (int) ; 
 int MCF_SDRAMC_SDCFG1_RDLAT (int) ; 
 int MCF_SDRAMC_SDCFG1_REF2ACT (int) ; 
 int MCF_SDRAMC_SDCFG1_SRD2RW (int) ; 
 int MCF_SDRAMC_SDCFG1_SWT2RD (scalar_t__) ; 
 int MCF_SDRAMC_SDCFG1_WTLAT (int) ; 
 int MCF_SDRAMC_SDCFG2 ; 
 int MCF_SDRAMC_SDCFG2_BL (int) ; 
 int MCF_SDRAMC_SDCFG2_BRD2PRE (int) ; 
 int MCF_SDRAMC_SDCFG2_BRD2WT (int) ; 
 int MCF_SDRAMC_SDCFG2_BWT2RW (scalar_t__) ; 
 int MCF_SDRAMC_SDCR ; 
 int MCF_SDRAMC_SDCR_CKE ; 
 int MCF_SDRAMC_SDCR_DDR ; 
 int MCF_SDRAMC_SDCR_DQS_OE (int) ; 
 int MCF_SDRAMC_SDCR_IPALL ; 
 int MCF_SDRAMC_SDCR_IREF ; 
 int MCF_SDRAMC_SDCR_MODE_EN ; 
 int MCF_SDRAMC_SDCR_MUX (int) ; 
 int MCF_SDRAMC_SDCR_PS_16 ; 
 int MCF_SDRAMC_SDCR_RCNT (int) ; 
 int MCF_SDRAMC_SDCR_REF ; 
 int MCF_SDRAMC_SDCS0 ; 
 int MCF_SDRAMC_SDCS_BA (int /*<<< orphan*/ ) ; 
 int MCF_SDRAMC_SDCS_CSSZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCF_SDRAMC_SDCS_CSSZ_32MBYTE ; 
 int MCF_SDRAMC_SDMR ; 
 int MCF_SDRAMC_SDMR_AD (int) ; 
 int MCF_SDRAMC_SDMR_BNKAD_LEMR ; 
 int MCF_SDRAMC_SDMR_BNKAD_LMR ; 
 int MCF_SDRAMC_SDMR_CMD ; 
 int /*<<< orphan*/  SDRAM_ADDRESS ; 
 int SDRAM_BL ; 
 int SDRAM_CASL ; 
 int SDRAM_TREFI ; 
 scalar_t__ SDRAM_TRFC ; 
 scalar_t__ SDRAM_TWR ; 
 int SYSTEM_PERIOD ; 

void sdramc_init(void)
{
	/*
	 * Check to see if the SDRAM has already been initialized
	 * by a run control tool
	 */
	if (!(MCF_SDRAMC_SDCR & MCF_SDRAMC_SDCR_REF)) {
		/* SDRAM chip select initialization */
		
		/* Initialize SDRAM chip select */
		MCF_SDRAMC_SDCS0 = (0
			| MCF_SDRAMC_SDCS_BA(SDRAM_ADDRESS)
			| MCF_SDRAMC_SDCS_CSSZ(MCF_SDRAMC_SDCS_CSSZ_32MBYTE));

	/*
	 * Basic configuration and initialization
	 */
	MCF_SDRAMC_SDCFG1 = (0
		| MCF_SDRAMC_SDCFG1_SRD2RW((int)((SDRAM_CASL + 2) + 0.5 ))
		| MCF_SDRAMC_SDCFG1_SWT2RD(SDRAM_TWR + 1)
		| MCF_SDRAMC_SDCFG1_RDLAT((int)((SDRAM_CASL*2) + 2))
		| MCF_SDRAMC_SDCFG1_ACT2RW((int)((SDRAM_TRCD ) + 0.5))
		| MCF_SDRAMC_SDCFG1_PRE2ACT((int)((SDRAM_TRP ) + 0.5))
		| MCF_SDRAMC_SDCFG1_REF2ACT((int)(((SDRAM_TRFC) ) + 0.5))
		| MCF_SDRAMC_SDCFG1_WTLAT(3));
	MCF_SDRAMC_SDCFG2 = (0
		| MCF_SDRAMC_SDCFG2_BRD2PRE(SDRAM_BL/2 + 1)
		| MCF_SDRAMC_SDCFG2_BWT2RW(SDRAM_BL/2 + SDRAM_TWR)
		| MCF_SDRAMC_SDCFG2_BRD2WT((int)((SDRAM_CASL+SDRAM_BL/2-1.0)+0.5))
		| MCF_SDRAMC_SDCFG2_BL(SDRAM_BL-1));

            
	/*
	 * Precharge and enable write to SDMR
	 */
        MCF_SDRAMC_SDCR = (0
		| MCF_SDRAMC_SDCR_MODE_EN
		| MCF_SDRAMC_SDCR_CKE
		| MCF_SDRAMC_SDCR_DDR
		| MCF_SDRAMC_SDCR_MUX(1)
		| MCF_SDRAMC_SDCR_RCNT((int)(((SDRAM_TREFI/(SYSTEM_PERIOD*64)) - 1) + 0.5))
		| MCF_SDRAMC_SDCR_PS_16
		| MCF_SDRAMC_SDCR_IPALL);            

	/*
	 * Write extended mode register
	 */
	MCF_SDRAMC_SDMR = (0
		| MCF_SDRAMC_SDMR_BNKAD_LEMR
		| MCF_SDRAMC_SDMR_AD(0x0)
		| MCF_SDRAMC_SDMR_CMD);

	/*
	 * Write mode register and reset DLL
	 */
	MCF_SDRAMC_SDMR = (0
		| MCF_SDRAMC_SDMR_BNKAD_LMR
		| MCF_SDRAMC_SDMR_AD(0x163)
		| MCF_SDRAMC_SDMR_CMD);

	/*
	 * Execute a PALL command
	 */
	MCF_SDRAMC_SDCR |= MCF_SDRAMC_SDCR_IPALL;

	/*
	 * Perform two REF cycles
	 */
	MCF_SDRAMC_SDCR |= MCF_SDRAMC_SDCR_IREF;
	MCF_SDRAMC_SDCR |= MCF_SDRAMC_SDCR_IREF;

	/*
	 * Write mode register and clear reset DLL
	 */
	MCF_SDRAMC_SDMR = (0
		| MCF_SDRAMC_SDMR_BNKAD_LMR
		| MCF_SDRAMC_SDMR_AD(0x063)
		| MCF_SDRAMC_SDMR_CMD);
				
	/*
	 * Enable auto refresh and lock SDMR
	 */
	MCF_SDRAMC_SDCR &= ~MCF_SDRAMC_SDCR_MODE_EN;
	MCF_SDRAMC_SDCR |= (0
		| MCF_SDRAMC_SDCR_REF
		| MCF_SDRAMC_SDCR_DQS_OE(0xC));
	}
}