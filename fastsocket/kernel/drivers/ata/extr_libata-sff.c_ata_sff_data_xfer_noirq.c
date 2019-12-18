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
struct ata_device {int dummy; } ;

/* Variables and functions */
 unsigned int ata_sff_data_xfer (struct ata_device*,unsigned char*,unsigned int,int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

unsigned int ata_sff_data_xfer_noirq(struct ata_device *dev, unsigned char *buf,
				     unsigned int buflen, int rw)
{
	unsigned long flags;
	unsigned int consumed;

	local_irq_save(flags);
	consumed = ata_sff_data_xfer(dev, buf, buflen, rw);
	local_irq_restore(flags);

	return consumed;
}