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
typedef  int /*<<< orphan*/  u32 ;
struct ssb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ SSB_CHIPCO_BCAST_ADDR ; 
 scalar_t__ SSB_CHIPCO_BCAST_DATA ; 
 scalar_t__ SSB_PCICORE_BCAST_ADDR ; 
 scalar_t__ SSB_PCICORE_BCAST_DATA ; 
 int /*<<< orphan*/  ssb_read32 (struct ssb_device*,scalar_t__) ; 
 int /*<<< orphan*/  ssb_write32 (struct ssb_device*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ssb_broadcast_value(struct ssb_device *dev,
				u32 address, u32 data)
{
#ifdef CONFIG_SSB_DRIVER_PCICORE
	/* This is used for both, PCI and ChipCommon core, so be careful. */
	BUILD_BUG_ON(SSB_PCICORE_BCAST_ADDR != SSB_CHIPCO_BCAST_ADDR);
	BUILD_BUG_ON(SSB_PCICORE_BCAST_DATA != SSB_CHIPCO_BCAST_DATA);
#endif

	ssb_write32(dev, SSB_CHIPCO_BCAST_ADDR, address);
	ssb_read32(dev, SSB_CHIPCO_BCAST_ADDR); /* flush */
	ssb_write32(dev, SSB_CHIPCO_BCAST_DATA, data);
	ssb_read32(dev, SSB_CHIPCO_BCAST_DATA); /* flush */
}