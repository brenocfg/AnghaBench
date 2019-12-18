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
 int EBUSY ; 
#define  EXT_IRQ0 133 
#define  EXT_IRQ1 132 
#define  EXT_IRQ2 131 
#define  EXT_IRQ3 130 
#define  EXT_IRQ4 129 
#define  EXT_IRQ5 128 
 int /*<<< orphan*/  H8300_GPIO_DDR (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H8300_GPIO_INPUT ; 
 int /*<<< orphan*/  H8300_GPIO_P8 ; 
 int /*<<< orphan*/  H8300_GPIO_P9 ; 
 int /*<<< orphan*/  H8300_GPIO_RESERVE (int /*<<< orphan*/ ,int) ; 

int h8300_enable_irq_pin(unsigned int irq)
{
	int bitmask;
	if (irq < EXT_IRQ0 || irq > EXT_IRQ5)
		return 0;

	/* initialize IRQ pin */
	bitmask = 1 << (irq - EXT_IRQ0);
	switch(irq) {
	case EXT_IRQ0:
	case EXT_IRQ1:
	case EXT_IRQ2:
	case EXT_IRQ3:
		if (H8300_GPIO_RESERVE(H8300_GPIO_P8, bitmask) == 0)
			return -EBUSY;
		H8300_GPIO_DDR(H8300_GPIO_P8, bitmask, H8300_GPIO_INPUT);
		break;
	case EXT_IRQ4:
	case EXT_IRQ5:
		if (H8300_GPIO_RESERVE(H8300_GPIO_P9, bitmask) == 0)
			return -EBUSY;
		H8300_GPIO_DDR(H8300_GPIO_P9, bitmask, H8300_GPIO_INPUT);
		break;
	}

	return 0;
}