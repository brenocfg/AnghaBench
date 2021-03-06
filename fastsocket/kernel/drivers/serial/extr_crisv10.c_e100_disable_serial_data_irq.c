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
 int /*<<< orphan*/  DINTR1 (int /*<<< orphan*/ ) ; 
 unsigned int* R_IRQ_MASK1_CLR ; 
 int /*<<< orphan*/  printk (char*,int) ; 

__attribute__((used)) static inline void
e100_disable_serial_data_irq(struct e100_serial *info)
{
#ifdef SERIAL_DEBUG_INTR
	printk("ser_irq(%d): 0\n",info->line);
#endif
	DINTR1(DEBUG_LOG(info->line,"IRQ disable data_irq %i\n", info->line));
	*R_IRQ_MASK1_CLR = (1U << (8+2*info->line));
}