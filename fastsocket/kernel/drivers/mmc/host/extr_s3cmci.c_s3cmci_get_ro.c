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
struct s3c24xx_mci_pdata {scalar_t__ wprotect_invert; int /*<<< orphan*/  gpio_wprotect; scalar_t__ no_wprotect; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 struct s3cmci_host* mmc_priv (struct mmc_host*) ; 
 int s3c2410_gpio_getpin (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s3cmci_get_ro(struct mmc_host *mmc)
{
	struct s3cmci_host *host = mmc_priv(mmc);
	struct s3c24xx_mci_pdata *pdata = host->pdata;
	int ret;

	if (pdata->no_wprotect)
		return 0;

	ret = s3c2410_gpio_getpin(pdata->gpio_wprotect);

	if (pdata->wprotect_invert)
		ret = !ret;

	return ret;
}