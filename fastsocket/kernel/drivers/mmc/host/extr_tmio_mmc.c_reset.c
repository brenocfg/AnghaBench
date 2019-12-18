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
struct tmio_mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_RESET_SD ; 
 int /*<<< orphan*/  CTL_RESET_SDIO ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  sd_ctrl_write16 (struct tmio_mmc_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void reset(struct tmio_mmc_host *host)
{
	/* FIXME - should we set stop clock reg here */
	sd_ctrl_write16(host, CTL_RESET_SD, 0x0000);
	sd_ctrl_write16(host, CTL_RESET_SDIO, 0x0000);
	msleep(10);
	sd_ctrl_write16(host, CTL_RESET_SD, 0x0001);
	sd_ctrl_write16(host, CTL_RESET_SDIO, 0x0001);
	msleep(10);
}