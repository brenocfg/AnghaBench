#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pxamci_host {int /*<<< orphan*/  mmc; TYPE_1__* pdata; scalar_t__ vcc; } ;
struct TYPE_2__ {int ocr_mask; int gpio_power_invert; int /*<<< orphan*/  (* setpower ) (int /*<<< orphan*/ ,unsigned int) ;int /*<<< orphan*/  gpio_power; } ;

/* Variables and functions */
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_regulator_set_ocr (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void pxamci_set_power(struct pxamci_host *host, unsigned int vdd)
{
	int on;

#ifdef CONFIG_REGULATOR
	if (host->vcc)
		mmc_regulator_set_ocr(host->vcc, vdd);
#endif
	if (!host->vcc && host->pdata &&
	    gpio_is_valid(host->pdata->gpio_power)) {
		on = ((1 << vdd) & host->pdata->ocr_mask);
		gpio_set_value(host->pdata->gpio_power,
			       !!on ^ host->pdata->gpio_power_invert);
	}
	if (!host->vcc && host->pdata && host->pdata->setpower)
		host->pdata->setpower(mmc_dev(host->mmc), vdd);
}