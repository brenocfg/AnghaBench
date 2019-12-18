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
struct mpc85xx_mc_pdata {scalar_t__ mc_vbase; } ;
struct mem_ctl_info {struct mpc85xx_mc_pdata* pvt_info; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ MPC85XX_MC_DATA_ERR_INJECT_LO ; 
 int in_be32 (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t mpc85xx_mc_inject_data_lo_show(struct mem_ctl_info *mci,
					      char *data)
{
	struct mpc85xx_mc_pdata *pdata = mci->pvt_info;
	return sprintf(data, "0x%08x",
		       in_be32(pdata->mc_vbase +
			       MPC85XX_MC_DATA_ERR_INJECT_LO));
}