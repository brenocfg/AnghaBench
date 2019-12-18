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
struct e100_serial {int line; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LOG (int,char*,int) ; 
 int /*<<< orphan*/  DINTR2 (int /*<<< orphan*/ ) ; 
 unsigned int* R_IRQ_MASK1_SET ; 
 int /*<<< orphan*/  printk (char*,int,...) ; 

__attribute__((used)) static inline void
e100_enable_serial_tx_ready_irq(struct e100_serial *info)
{
#ifdef SERIAL_DEBUG_INTR
	printk("ser_tx_irq(%d): 1\n",info->line);
	printk("**** %d = %d\n",
	       (8+1+2*info->line),
	       (1U << (8+1+2*info->line)));
#endif
	DINTR2(DEBUG_LOG(info->line,"IRQ enable ready_irq %i\n", info->line));
	*R_IRQ_MASK1_SET = (1U << (8+1+2*info->line));
}