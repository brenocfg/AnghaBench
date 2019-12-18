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
#define  EXT_IRQ0 133 
#define  EXT_IRQ1 132 
#define  EXT_IRQ2 131 
#define  EXT_IRQ3 130 
#define  EXT_IRQ4 129 
#define  EXT_IRQ5 128 
 int /*<<< orphan*/  H8300_GPIO_FREE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  H8300_GPIO_P8 ; 
 int /*<<< orphan*/  H8300_GPIO_P9 ; 
 scalar_t__ IER ; 

void h8300_disable_irq_pin(unsigned int irq)
{
	int bitmask;
	if (irq < EXT_IRQ0 || irq > EXT_IRQ5)
		return;

	/* disable interrupt & release IRQ pin */
	bitmask = 1 << (irq - EXT_IRQ0);
	switch(irq) {
	case EXT_IRQ0:
	case EXT_IRQ1:
	case EXT_IRQ2:
	case EXT_IRQ3:
		*(volatile unsigned char *)IER &= ~bitmask;
		H8300_GPIO_FREE(H8300_GPIO_P8, bitmask);
		break ;
	case EXT_IRQ4:
	case EXT_IRQ5:
		*(volatile unsigned char *)IER &= ~bitmask;
		H8300_GPIO_FREE(H8300_GPIO_P9, bitmask);
		break;
	}
}