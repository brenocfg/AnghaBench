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
struct TYPE_2__ {int iTCO_version; int /*<<< orphan*/  pdev; int /*<<< orphan*/  gcs; } ;

/* Variables and functions */
 int EIO ; 
 TYPE_1__ iTCO_wdt_private ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int,int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iTCO_wdt_unset_NO_REBOOT_bit(void)
{
	int ret = 0;
	u32 val32;

	/* Unset the NO_REBOOT bit: this enables reboots */
	if (iTCO_wdt_private.iTCO_version == 2) {
		val32 = readl(iTCO_wdt_private.gcs);
		val32 &= 0xffffffdf;
		writel(val32, iTCO_wdt_private.gcs);

		val32 = readl(iTCO_wdt_private.gcs);
		if (val32 & 0x00000020)
			ret = -EIO;
	} else if (iTCO_wdt_private.iTCO_version == 1) {
		pci_read_config_dword(iTCO_wdt_private.pdev, 0xd4, &val32);
		val32 &= 0xfffffffd;
		pci_write_config_dword(iTCO_wdt_private.pdev, 0xd4, val32);

		pci_read_config_dword(iTCO_wdt_private.pdev, 0xd4, &val32);
		if (val32 & 0x00000002)
			ret = -EIO;
	}

	return ret; /* returns: 0 = OK, -EIO = Error */
}