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
struct ata_device {int /*<<< orphan*/  max_sectors; } ;

/* Variables and functions */
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void octeon_cf_dev_config(struct ata_device *dev)
{
	/*
	 * A maximum of 2^20 - 1 16 bit transfers are possible with
	 * the bootbus DMA.  So we need to throttle max_sectors to
	 * (2^12 - 1 == 4095) to assure that this can never happen.
	 */
	dev->max_sectors = min(dev->max_sectors, 4095U);
}