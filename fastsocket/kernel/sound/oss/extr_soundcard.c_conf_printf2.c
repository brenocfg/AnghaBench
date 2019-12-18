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

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,...) ; 

void conf_printf2(char *name, int base, int irq, int dma, int dma2)
{
#ifndef CONFIG_SOUND_TRACEINIT
	return;
#else
	printk("<%s> at 0x%03x", name, base);

	if (irq)
		printk(" irq %d", (irq > 0) ? irq : -irq);

	if (dma != -1 || dma2 != -1)
	{
		  printk(" dma %d", dma);
		  if (dma2 != -1)
			  printk(",%d", dma2);
	}
	printk("\n");
#endif
}