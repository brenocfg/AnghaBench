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
struct ccdc_fault_pixel {int fpc_table_addr; int fp_num; int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCDC_FPC ; 
 int /*<<< orphan*/  CCDC_FPC_ADDR ; 
 int CCDC_FPC_DISABLE ; 
 int CCDC_FPC_ENABLE ; 
 int CCDC_FPC_FPC_NUM_MASK ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int regr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regw (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccdc_config_fpc(struct ccdc_fault_pixel *fpc)
{
	u32 val;

	/* Initially disable FPC */
	val = CCDC_FPC_DISABLE;
	regw(val, CCDC_FPC);

	if (!fpc->enable)
		return;

	/* Configure Fault pixel if needed */
	regw(fpc->fpc_table_addr, CCDC_FPC_ADDR);
	dev_dbg(dev, "\nWriting 0x%x to FPC_ADDR...\n",
		       (fpc->fpc_table_addr));
	/* Write the FPC params with FPC disable */
	val = fpc->fp_num & CCDC_FPC_FPC_NUM_MASK;
	regw(val, CCDC_FPC);

	dev_dbg(dev, "\nWriting 0x%x to FPC...\n", val);
	/* read the FPC register */
	val = regr(CCDC_FPC) | CCDC_FPC_ENABLE;
	regw(val, CCDC_FPC);
	dev_dbg(dev, "\nWriting 0x%x to FPC...\n", val);
}