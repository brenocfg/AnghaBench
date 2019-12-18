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
 int /*<<< orphan*/  DELAY_16 () ; 
 scalar_t__ ELMC_CTRL ; 
 int ELMC_CTRL_LBK ; 
 int ELMC_CTRL_RST ; 
 int /*<<< orphan*/  elmc_do_attn586 (int,int) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void elmc_do_reset586(int ioaddr, int ints)
{
	/* toggle the RST bit low then high */
	outb(0x3 | ELMC_CTRL_LBK, ioaddr + ELMC_CTRL);
	DELAY_16();		/* > 500 ns */
	outb(ELMC_CTRL_RST | ELMC_CTRL_LBK | 0x3, ioaddr + ELMC_CTRL);

	elmc_do_attn586(ioaddr, ints);
}