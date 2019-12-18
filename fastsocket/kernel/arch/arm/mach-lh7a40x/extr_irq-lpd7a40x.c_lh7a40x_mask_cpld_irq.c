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
 int CPLD_INTERRUPTS ; 
#define  IRQ_LPD7A400_TS 129 
#define  IRQ_LPD7A40X_ETH_INT 128 

__attribute__((used)) static void lh7a40x_mask_cpld_irq (u32 irq)
{
	switch (irq) {
	case IRQ_LPD7A40X_ETH_INT:
		CPLD_INTERRUPTS = CPLD_INTERRUPTS | 0x4;
		break;
	case IRQ_LPD7A400_TS:
		CPLD_INTERRUPTS = CPLD_INTERRUPTS | 0x8;
		break;
	}
}