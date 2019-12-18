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
typedef  int u32 ;
struct tmio_mmc_host {TYPE_1__* mmc; } ;
struct TYPE_2__ {int f_min; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNF_SD_CLK_MODE ; 
 int /*<<< orphan*/  CTL_SD_CARD_CLK_CTL ; 
 int /*<<< orphan*/  sd_config_write8 (struct tmio_mmc_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sd_ctrl_write16 (struct tmio_mmc_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tmio_mmc_set_clock(struct tmio_mmc_host *host, int new_clock)
{
	u32 clk = 0, clock;

	if (new_clock) {
		for (clock = host->mmc->f_min, clk = 0x80000080;
			new_clock >= (clock<<1); clk >>= 1)
			clock <<= 1;
		clk |= 0x100;
	}

	sd_config_write8(host, CNF_SD_CLK_MODE, clk >> 22);
	sd_ctrl_write16(host, CTL_SD_CARD_CLK_CTL, clk & 0x1ff);
}