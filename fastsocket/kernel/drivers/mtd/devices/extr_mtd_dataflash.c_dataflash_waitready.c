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
struct spi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MTD_DEBUG_LEVEL1 ; 
 int dataflash_status (struct spi_device*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int dataflash_waitready(struct spi_device *spi)
{
	int	status;

	for (;;) {
		status = dataflash_status(spi);
		if (status < 0) {
			DEBUG(MTD_DEBUG_LEVEL1, "%s: status %d?\n",
					dev_name(&spi->dev), status);
			status = 0;
		}

		if (status & (1 << 7))	/* RDY/nBSY */
			return status;

		msleep(3);
	}
}