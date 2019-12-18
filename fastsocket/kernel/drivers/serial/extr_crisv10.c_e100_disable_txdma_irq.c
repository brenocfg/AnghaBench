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
struct e100_serial {int /*<<< orphan*/  irq; int /*<<< orphan*/  line; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LOG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DINTR1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * R_IRQ_MASK2_CLR ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e100_disable_txdma_irq(struct e100_serial *info)
{
#ifdef SERIAL_DEBUG_INTR
	printk("txdma_irq(%d): 0\n",info->line);
#endif
	DINTR1(DEBUG_LOG(info->line,"IRQ disable_txdma_irq %i\n", info->line));
	*R_IRQ_MASK2_CLR = info->irq;
}