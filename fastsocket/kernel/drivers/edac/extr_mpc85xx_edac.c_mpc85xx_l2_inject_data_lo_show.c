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
struct mpc85xx_l2_pdata {scalar_t__ l2_vbase; } ;
struct edac_device_ctl_info {struct mpc85xx_l2_pdata* pvt_info; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ MPC85XX_L2_ERRINJLO ; 
 int in_be32 (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t mpc85xx_l2_inject_data_lo_show(struct edac_device_ctl_info
					      *edac_dev, char *data)
{
	struct mpc85xx_l2_pdata *pdata = edac_dev->pvt_info;
	return sprintf(data, "0x%08x",
		       in_be32(pdata->l2_vbase + MPC85XX_L2_ERRINJLO));
}