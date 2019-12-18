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
typedef  int u32 ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * irq_name ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void bttv_print_irqbits(u32 print, u32 mark)
{
	unsigned int i;

	printk("bits:");
	for (i = 0; i < ARRAY_SIZE(irq_name); i++) {
		if (print & (1 << i))
			printk(" %s",irq_name[i]);
		if (mark & (1 << i))
			printk("*");
	}
}