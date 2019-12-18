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
typedef  scalar_t__ u16 ;
struct ata_device {int /*<<< orphan*/ * gscr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  ata_dev_printk (struct ata_device*,int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ sata_pmp_gscr_devid (int /*<<< orphan*/  const*) ; 
 int sata_pmp_gscr_ports (int /*<<< orphan*/  const*) ; 
 scalar_t__ sata_pmp_gscr_vendor (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int sata_pmp_same_pmp(struct ata_device *dev, const u32 *new_gscr)
{
	const u32 *old_gscr = dev->gscr;
	u16 old_vendor, new_vendor, old_devid, new_devid;
	int old_nr_ports, new_nr_ports;

	old_vendor = sata_pmp_gscr_vendor(old_gscr);
	new_vendor = sata_pmp_gscr_vendor(new_gscr);
	old_devid = sata_pmp_gscr_devid(old_gscr);
	new_devid = sata_pmp_gscr_devid(new_gscr);
	old_nr_ports = sata_pmp_gscr_ports(old_gscr);
	new_nr_ports = sata_pmp_gscr_ports(new_gscr);

	if (old_vendor != new_vendor) {
		ata_dev_printk(dev, KERN_INFO, "Port Multiplier "
			       "vendor mismatch '0x%x' != '0x%x'\n",
			       old_vendor, new_vendor);
		return 0;
	}

	if (old_devid != new_devid) {
		ata_dev_printk(dev, KERN_INFO, "Port Multiplier "
			       "device ID mismatch '0x%x' != '0x%x'\n",
			       old_devid, new_devid);
		return 0;
	}

	if (old_nr_ports != new_nr_ports) {
		ata_dev_printk(dev, KERN_INFO, "Port Multiplier "
			       "nr_ports mismatch '0x%x' != '0x%x'\n",
			       old_nr_ports, new_nr_ports);
		return 0;
	}

	return 1;
}