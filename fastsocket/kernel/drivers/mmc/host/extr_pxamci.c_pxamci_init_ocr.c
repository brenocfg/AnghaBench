#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pxamci_host {TYPE_1__* pdata; TYPE_2__* mmc; int /*<<< orphan*/ * vcc; } ;
struct TYPE_4__ {int ocr_avail; } ;
struct TYPE_3__ {int ocr_mask; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int MMC_VDD_32_33 ; 
 int MMC_VDD_33_34 ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (TYPE_2__*) ; 
 int mmc_regulator_get_ocrmask (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * regulator_get (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline void pxamci_init_ocr(struct pxamci_host *host)
{
#ifdef CONFIG_REGULATOR
	host->vcc = regulator_get(mmc_dev(host->mmc), "vmmc");

	if (IS_ERR(host->vcc))
		host->vcc = NULL;
	else {
		host->mmc->ocr_avail = mmc_regulator_get_ocrmask(host->vcc);
		if (host->pdata && host->pdata->ocr_mask)
			dev_warn(mmc_dev(host->mmc),
				"ocr_mask/setpower will not be used\n");
	}
#endif
	if (host->vcc == NULL) {
		/* fall-back to platform data */
		host->mmc->ocr_avail = host->pdata ?
			host->pdata->ocr_mask :
			MMC_VDD_32_33 | MMC_VDD_33_34;
	}
}