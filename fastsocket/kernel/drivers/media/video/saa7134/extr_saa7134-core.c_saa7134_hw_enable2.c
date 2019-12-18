#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct saa7134_dev {scalar_t__ has_remote; TYPE_1__* remote; } ;
struct TYPE_2__ {int mask_keydown; int mask_keyup; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7134_IRQ1 ; 
 int /*<<< orphan*/  SAA7134_IRQ2 ; 
 unsigned int SAA7134_IRQ2_INTE_AR ; 
 unsigned int SAA7134_IRQ2_INTE_DEC0 ; 
 unsigned int SAA7134_IRQ2_INTE_DEC1 ; 
 unsigned int SAA7134_IRQ2_INTE_DEC2 ; 
 unsigned int SAA7134_IRQ2_INTE_DEC3 ; 
 unsigned int SAA7134_IRQ2_INTE_GPIO16_N ; 
 unsigned int SAA7134_IRQ2_INTE_GPIO18_N ; 
 unsigned int SAA7134_IRQ2_INTE_GPIO18_P ; 
 unsigned int SAA7134_IRQ2_INTE_PE ; 
 scalar_t__ SAA7134_REMOTE_GPIO ; 
 scalar_t__ SAA7134_REMOTE_I2C ; 
 int /*<<< orphan*/  request_module (char*) ; 
 int /*<<< orphan*/  saa_writel (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int saa7134_hw_enable2(struct saa7134_dev *dev)
{

	unsigned int irq2_mask;

	/* enable IRQ's */
	irq2_mask =
		SAA7134_IRQ2_INTE_DEC3    |
		SAA7134_IRQ2_INTE_DEC2    |
		SAA7134_IRQ2_INTE_DEC1    |
		SAA7134_IRQ2_INTE_DEC0    |
		SAA7134_IRQ2_INTE_PE      |
		SAA7134_IRQ2_INTE_AR;

	if (dev->has_remote == SAA7134_REMOTE_GPIO && dev->remote) {
		if (dev->remote->mask_keydown & 0x10000)
			irq2_mask |= SAA7134_IRQ2_INTE_GPIO16_N;
		else {		/* Allow enabling both IRQ edge triggers */
			if (dev->remote->mask_keydown & 0x40000)
				irq2_mask |= SAA7134_IRQ2_INTE_GPIO18_P;
			if (dev->remote->mask_keyup & 0x40000)
				irq2_mask |= SAA7134_IRQ2_INTE_GPIO18_N;
		}
	}

	if (dev->has_remote == SAA7134_REMOTE_I2C) {
		request_module("ir-kbd-i2c");
	}

	saa_writel(SAA7134_IRQ1, 0);
	saa_writel(SAA7134_IRQ2, irq2_mask);

	return 0;
}