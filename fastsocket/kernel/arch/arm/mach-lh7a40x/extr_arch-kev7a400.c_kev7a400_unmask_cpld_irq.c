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
 int CPLD_IRQ_mask ; 
 int CPLD_WR_PB_INT_MASK ; 
 int IRQ_KEV7A400_CPLD ; 

__attribute__((used)) static void kev7a400_unmask_cpld_irq (u32 irq)
{
	CPLD_IRQ_mask |= 1 << (irq - IRQ_KEV7A400_CPLD);
	CPLD_WR_PB_INT_MASK = CPLD_IRQ_mask;
}