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
struct ata_device {int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int EIO ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  ata_dev_printk (struct ata_device*,int /*<<< orphan*/ ,char*,int,unsigned int) ; 
 unsigned int sata_pmp_read (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sata_pmp_read_gscr(struct ata_device *dev, u32 *gscr)
{
	static const int gscr_to_read[] = { 0, 1, 2, 32, 33, 64, 96 };
	int i;

	for (i = 0; i < ARRAY_SIZE(gscr_to_read); i++) {
		int reg = gscr_to_read[i];
		unsigned int err_mask;

		err_mask = sata_pmp_read(dev->link, reg, &gscr[reg]);
		if (err_mask) {
			ata_dev_printk(dev, KERN_ERR, "failed to read PMP "
				"GSCR[%d] (Emask=0x%x)\n", reg, err_mask);
			return -EIO;
		}
	}

	return 0;
}