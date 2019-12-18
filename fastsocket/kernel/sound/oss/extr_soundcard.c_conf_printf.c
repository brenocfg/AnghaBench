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
struct address_info {int irq; int dma; int dma2; int /*<<< orphan*/  io_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,...) ; 

void conf_printf(char *name, struct address_info *hw_config)
{
#ifndef CONFIG_SOUND_TRACEINIT
	return;
#else
	printk("<%s> at 0x%03x", name, hw_config->io_base);

	if (hw_config->irq)
		printk(" irq %d", (hw_config->irq > 0) ? hw_config->irq : -hw_config->irq);

	if (hw_config->dma != -1 || hw_config->dma2 != -1)
	{
		printk(" dma %d", hw_config->dma);
		if (hw_config->dma2 != -1)
			printk(",%d", hw_config->dma2);
	}
	printk("\n");
#endif
}