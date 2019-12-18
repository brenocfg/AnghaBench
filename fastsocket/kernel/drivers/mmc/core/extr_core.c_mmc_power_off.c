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
struct TYPE_2__ {int /*<<< orphan*/  timing; int /*<<< orphan*/  bus_width; int /*<<< orphan*/  power_mode; int /*<<< orphan*/  chip_select; int /*<<< orphan*/  bus_mode; scalar_t__ vdd; scalar_t__ clock; } ;
struct mmc_host {TYPE_1__ ios; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_BUSMODE_OPENDRAIN ; 
 int /*<<< orphan*/  MMC_BUS_WIDTH_1 ; 
 int /*<<< orphan*/  MMC_CS_DONTCARE ; 
 int /*<<< orphan*/  MMC_POWER_OFF ; 
 int /*<<< orphan*/  MMC_TIMING_LEGACY ; 
 int /*<<< orphan*/  mmc_host_is_spi (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_set_ios (struct mmc_host*) ; 

__attribute__((used)) static void mmc_power_off(struct mmc_host *host)
{
	host->ios.clock = 0;
	host->ios.vdd = 0;
	if (!mmc_host_is_spi(host)) {
		host->ios.bus_mode = MMC_BUSMODE_OPENDRAIN;
		host->ios.chip_select = MMC_CS_DONTCARE;
	}
	host->ios.power_mode = MMC_POWER_OFF;
	host->ios.bus_width = MMC_BUS_WIDTH_1;
	host->ios.timing = MMC_TIMING_LEGACY;
	mmc_set_ios(host);
}