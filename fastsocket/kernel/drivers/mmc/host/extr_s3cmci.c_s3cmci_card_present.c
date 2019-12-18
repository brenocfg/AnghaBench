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
struct s3cmci_host {struct s3c24xx_mci_pdata* pdata; } ;
struct s3c24xx_mci_pdata {scalar_t__ gpio_detect; int detect_invert; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
 scalar_t__ gpio_get_value (scalar_t__) ; 
 struct s3cmci_host* mmc_priv (struct mmc_host*) ; 

__attribute__((used)) static int s3cmci_card_present(struct mmc_host *mmc)
{
	struct s3cmci_host *host = mmc_priv(mmc);
	struct s3c24xx_mci_pdata *pdata = host->pdata;
	int ret;

	if (pdata->gpio_detect == 0)
		return -ENOSYS;

	ret = gpio_get_value(pdata->gpio_detect) ? 0 : 1;
	return ret ^ pdata->detect_invert;
}