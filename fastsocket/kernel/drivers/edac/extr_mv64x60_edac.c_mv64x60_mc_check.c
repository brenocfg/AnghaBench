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
struct mv64x60_mc_pdata {scalar_t__ mc_vbase; } ;
struct mem_ctl_info {int /*<<< orphan*/  ctl_name; struct mv64x60_mc_pdata* pvt_info; } ;

/* Variables and functions */
 scalar_t__ MV64X60_SDRAM_ERR_ADDR ; 
 scalar_t__ MV64X60_SDRAM_ERR_ECC_CALC ; 
 scalar_t__ MV64X60_SDRAM_ERR_ECC_RCVD ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  edac_mc_handle_ce (struct mem_ctl_info*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_mc_handle_ue (struct mem_ctl_info*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int in_le32 (scalar_t__) ; 
 int /*<<< orphan*/  out_le32 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mv64x60_mc_check(struct mem_ctl_info *mci)
{
	struct mv64x60_mc_pdata *pdata = mci->pvt_info;
	u32 reg;
	u32 err_addr;
	u32 sdram_ecc;
	u32 comp_ecc;
	u32 syndrome;

	reg = in_le32(pdata->mc_vbase + MV64X60_SDRAM_ERR_ADDR);
	if (!reg)
		return;

	err_addr = reg & ~0x3;
	sdram_ecc = in_le32(pdata->mc_vbase + MV64X60_SDRAM_ERR_ECC_RCVD);
	comp_ecc = in_le32(pdata->mc_vbase + MV64X60_SDRAM_ERR_ECC_CALC);
	syndrome = sdram_ecc ^ comp_ecc;

	/* first bit clear in ECC Err Reg, 1 bit error, correctable by HW */
	if (!(reg & 0x1))
		edac_mc_handle_ce(mci, err_addr >> PAGE_SHIFT,
				  err_addr & PAGE_MASK, syndrome, 0, 0,
				  mci->ctl_name);
	else	/* 2 bit error, UE */
		edac_mc_handle_ue(mci, err_addr >> PAGE_SHIFT,
				  err_addr & PAGE_MASK, 0, mci->ctl_name);

	/* clear the error */
	out_le32(pdata->mc_vbase + MV64X60_SDRAM_ERR_ADDR, 0);
}