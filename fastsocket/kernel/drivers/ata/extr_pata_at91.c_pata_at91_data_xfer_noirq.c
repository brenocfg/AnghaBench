#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ata_device {TYPE_3__* link; } ;
struct at91_ide_info {int /*<<< orphan*/  cs; } ;
struct TYPE_6__ {TYPE_2__* ap; } ;
struct TYPE_5__ {TYPE_1__* host; } ;
struct TYPE_4__ {struct at91_ide_info* private_data; } ;

/* Variables and functions */
 unsigned int AT91_SMC_DBW ; 
 unsigned int AT91_SMC_DBW_16 ; 
 unsigned int AT91_SMC_DBW_8 ; 
 int /*<<< orphan*/  AT91_SMC_MODE (int /*<<< orphan*/ ) ; 
 unsigned int at91_sys_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_sys_write (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int ata_sff_data_xfer (struct ata_device*,unsigned char*,unsigned int,int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static unsigned int pata_at91_data_xfer_noirq(struct ata_device *dev,
		unsigned char *buf, unsigned int buflen, int rw)
{
	struct at91_ide_info *info = dev->link->ap->host->private_data;
	unsigned int consumed;
	unsigned long flags;
	unsigned int mode;

	local_irq_save(flags);
	mode = at91_sys_read(AT91_SMC_MODE(info->cs));

	/* set 16bit mode before writing data */
	at91_sys_write(AT91_SMC_MODE(info->cs),
			(mode & ~AT91_SMC_DBW) | AT91_SMC_DBW_16);

	consumed = ata_sff_data_xfer(dev, buf, buflen, rw);

	/* restore 8bit mode after data is written */
	at91_sys_write(AT91_SMC_MODE(info->cs),
			(mode & ~AT91_SMC_DBW) | AT91_SMC_DBW_8);

	local_irq_restore(flags);
	return consumed;
}