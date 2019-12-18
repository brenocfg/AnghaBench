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
typedef  int u16 ;
struct mmc_request {int dummy; } ;
struct mmc_omap_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTO ; 
 int OMAP_MMC_READ (struct mmc_omap_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OMAP_MMC_WRITE (struct mmc_omap_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SDIO ; 

__attribute__((used)) static inline void set_cmd_timeout(struct mmc_omap_host *host, struct mmc_request *req)
{
	u16 reg;

	reg = OMAP_MMC_READ(host, SDIO);
	reg &= ~(1 << 5);
	OMAP_MMC_WRITE(host, SDIO, reg);
	/* Set maximum timeout */
	OMAP_MMC_WRITE(host, CTO, 0xff);
}