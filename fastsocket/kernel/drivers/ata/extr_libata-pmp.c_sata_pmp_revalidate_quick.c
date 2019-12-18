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
typedef  scalar_t__ u32 ;
struct ata_device {scalar_t__* gscr; int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  KERN_ERR ; 
 size_t SATA_PMP_GSCR_PROD_ID ; 
 int /*<<< orphan*/  ata_dev_printk (struct ata_device*,int /*<<< orphan*/ ,char*,...) ; 
 unsigned int sata_pmp_read (int /*<<< orphan*/ ,size_t,scalar_t__*) ; 

__attribute__((used)) static int sata_pmp_revalidate_quick(struct ata_device *dev)
{
	unsigned int err_mask;
	u32 prod_id;

	err_mask = sata_pmp_read(dev->link, SATA_PMP_GSCR_PROD_ID, &prod_id);
	if (err_mask) {
		ata_dev_printk(dev, KERN_ERR, "failed to read PMP product ID "
			       "(Emask=0x%x)\n", err_mask);
		return -EIO;
	}

	if (prod_id != dev->gscr[SATA_PMP_GSCR_PROD_ID]) {
		ata_dev_printk(dev, KERN_ERR, "PMP product ID mismatch\n");
		/* something weird is going on, request full PMP recovery */
		return -EIO;
	}

	return 0;
}