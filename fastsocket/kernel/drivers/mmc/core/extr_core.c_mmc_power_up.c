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
struct TYPE_2__ {int vdd; int clock; int /*<<< orphan*/  power_mode; int /*<<< orphan*/  timing; int /*<<< orphan*/  bus_width; int /*<<< orphan*/  bus_mode; int /*<<< orphan*/  chip_select; } ;
struct mmc_host {int f_min; TYPE_1__ ios; int /*<<< orphan*/  ocr_avail; scalar_t__ ocr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_BUSMODE_OPENDRAIN ; 
 int /*<<< orphan*/  MMC_BUSMODE_PUSHPULL ; 
 int /*<<< orphan*/  MMC_BUS_WIDTH_1 ; 
 int /*<<< orphan*/  MMC_CS_DONTCARE ; 
 int /*<<< orphan*/  MMC_CS_HIGH ; 
 int /*<<< orphan*/  MMC_POWER_ON ; 
 int /*<<< orphan*/  MMC_POWER_UP ; 
 int /*<<< orphan*/  MMC_TIMING_LEGACY ; 
 int ffs (scalar_t__) ; 
 int fls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_delay (int) ; 
 scalar_t__ mmc_host_is_spi (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_set_ios (struct mmc_host*) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mmc_power_up(struct mmc_host *host)
{
	int bit;

	/* If ocr is set, we use it */
	if (host->ocr)
		bit = ffs(host->ocr) - 1;
	else
		bit = fls(host->ocr_avail) - 1;

	host->ios.vdd = bit;
	if (mmc_host_is_spi(host)) {
		host->ios.chip_select = MMC_CS_HIGH;
		host->ios.bus_mode = MMC_BUSMODE_PUSHPULL;
	} else {
		host->ios.chip_select = MMC_CS_DONTCARE;
		host->ios.bus_mode = MMC_BUSMODE_OPENDRAIN;
	}
	host->ios.power_mode = MMC_POWER_UP;
	host->ios.bus_width = MMC_BUS_WIDTH_1;
	host->ios.timing = MMC_TIMING_LEGACY;
	mmc_set_ios(host);

	/*
	 * This delay should be sufficient to allow the power supply
	 * to reach the minimum voltage.
	 */
	mmc_delay(10);

	if (host->f_min > 400000) {
		pr_warning("%s: Minimum clock frequency too high for "
				"identification mode\n", mmc_hostname(host));
		host->ios.clock = host->f_min;
	} else
		host->ios.clock = 400000;

	host->ios.power_mode = MMC_POWER_ON;
	mmc_set_ios(host);

	/*
	 * This delay must be at least 74 clock sizes, or 1 ms, or the
	 * time required to reach a stable voltage.
	 */
	mmc_delay(10);
}