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
 scalar_t__ PSC_CMD_BASE ; 
 scalar_t__ PSC_CTL_BASE ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  psc_write_word (scalar_t__,int) ; 

__attribute__((used)) static void psc_dma_die_die_die(void)
{
	int i;

	printk("Killing all PSC DMA channels...");
	for (i = 0 ; i < 9 ; i++) {
		psc_write_word(PSC_CTL_BASE + (i << 4), 0x8800);
		psc_write_word(PSC_CTL_BASE + (i << 4), 0x1000);
		psc_write_word(PSC_CMD_BASE + (i << 5), 0x1100);
		psc_write_word(PSC_CMD_BASE + (i << 5) + 0x10, 0x1100);
	}
	printk("done!\n");
}