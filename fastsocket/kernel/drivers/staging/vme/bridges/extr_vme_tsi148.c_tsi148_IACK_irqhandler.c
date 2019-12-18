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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  TSI148_LCSR_INTC_IACKC ; 
 int /*<<< orphan*/  iack_queue ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 tsi148_IACK_irqhandler(void)
{
	printk("tsi148_IACK_irqhandler\n");
	wake_up(&iack_queue);

	return TSI148_LCSR_INTC_IACKC;
}