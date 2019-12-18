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
struct mpc85xx_mc_pdata {scalar_t__ mc_vbase; } ;
struct mem_ctl_info {int nr_csrows; int /*<<< orphan*/  ctl_name; struct csrow_info* csrows; struct mpc85xx_mc_pdata* pvt_info; } ;
struct csrow_info {int first_page; int last_page; } ;

/* Variables and functions */
 int DDR_EDE_MBE ; 
 int DDR_EDE_SBE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 scalar_t__ MPC85XX_MC_CAPTURE_ADDRESS ; 
 scalar_t__ MPC85XX_MC_CAPTURE_DATA_HI ; 
 scalar_t__ MPC85XX_MC_CAPTURE_DATA_LO ; 
 scalar_t__ MPC85XX_MC_CAPTURE_ECC ; 
 scalar_t__ MPC85XX_MC_ERR_DETECT ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  edac_mc_handle_ce (struct mem_ctl_info*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_mc_handle_ue (struct mem_ctl_info*,int,int,int,int /*<<< orphan*/ ) ; 
 int in_be32 (scalar_t__) ; 
 int /*<<< orphan*/  mpc85xx_mc_printk (struct mem_ctl_info*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  out_be32 (scalar_t__,int) ; 

__attribute__((used)) static void mpc85xx_mc_check(struct mem_ctl_info *mci)
{
	struct mpc85xx_mc_pdata *pdata = mci->pvt_info;
	struct csrow_info *csrow;
	u32 err_detect;
	u32 syndrome;
	u32 err_addr;
	u32 pfn;
	int row_index;

	err_detect = in_be32(pdata->mc_vbase + MPC85XX_MC_ERR_DETECT);
	if (!err_detect)
		return;

	mpc85xx_mc_printk(mci, KERN_ERR, "Err Detect Register: %#8.8x\n",
			  err_detect);

	/* no more processing if not ECC bit errors */
	if (!(err_detect & (DDR_EDE_SBE | DDR_EDE_MBE))) {
		out_be32(pdata->mc_vbase + MPC85XX_MC_ERR_DETECT, err_detect);
		return;
	}

	syndrome = in_be32(pdata->mc_vbase + MPC85XX_MC_CAPTURE_ECC);
	err_addr = in_be32(pdata->mc_vbase + MPC85XX_MC_CAPTURE_ADDRESS);
	pfn = err_addr >> PAGE_SHIFT;

	for (row_index = 0; row_index < mci->nr_csrows; row_index++) {
		csrow = &mci->csrows[row_index];
		if ((pfn >= csrow->first_page) && (pfn <= csrow->last_page))
			break;
	}

	mpc85xx_mc_printk(mci, KERN_ERR, "Capture Data High: %#8.8x\n",
			  in_be32(pdata->mc_vbase +
				  MPC85XX_MC_CAPTURE_DATA_HI));
	mpc85xx_mc_printk(mci, KERN_ERR, "Capture Data Low: %#8.8x\n",
			  in_be32(pdata->mc_vbase +
				  MPC85XX_MC_CAPTURE_DATA_LO));
	mpc85xx_mc_printk(mci, KERN_ERR, "syndrome: %#8.8x\n", syndrome);
	mpc85xx_mc_printk(mci, KERN_ERR, "err addr: %#8.8x\n", err_addr);
	mpc85xx_mc_printk(mci, KERN_ERR, "PFN: %#8.8x\n", pfn);

	/* we are out of range */
	if (row_index == mci->nr_csrows)
		mpc85xx_mc_printk(mci, KERN_ERR, "PFN out of range!\n");

	if (err_detect & DDR_EDE_SBE)
		edac_mc_handle_ce(mci, pfn, err_addr & PAGE_MASK,
				  syndrome, row_index, 0, mci->ctl_name);

	if (err_detect & DDR_EDE_MBE)
		edac_mc_handle_ue(mci, pfn, err_addr & PAGE_MASK,
				  row_index, mci->ctl_name);

	out_be32(pdata->mc_vbase + MPC85XX_MC_ERR_DETECT, err_detect);
}