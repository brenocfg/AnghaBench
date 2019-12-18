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
struct resource {int dummy; } ;
struct mpu_config {int /*<<< orphan*/  osp; scalar_t__ opened; scalar_t__ initialized; int /*<<< orphan*/  irq; scalar_t__ base; } ;
struct address_info {scalar_t__ io_base; scalar_t__ always_detect; int /*<<< orphan*/  osp; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDB (int /*<<< orphan*/ ) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,scalar_t__) ; 
 int reset_mpu401 (struct mpu_config*) ; 

int probe_mpu401(struct address_info *hw_config, struct resource *ports)
{
	int ok = 0;
	struct mpu_config tmp_devc;

	tmp_devc.base = hw_config->io_base;
	tmp_devc.irq = hw_config->irq;
	tmp_devc.initialized = 0;
	tmp_devc.opened = 0;
	tmp_devc.osp = hw_config->osp;

	if (hw_config->always_detect)
		return 1;

	if (inb(hw_config->io_base + 1) == 0xff)
	{
		DDB(printk("MPU401: Port %x looks dead.\n", hw_config->io_base));
		return 0;	/* Just bus float? */
	}
	ok = reset_mpu401(&tmp_devc);

	if (!ok)
	{
		DDB(printk("MPU401: Reset failed on port %x\n", hw_config->io_base));
	}
	return ok;
}