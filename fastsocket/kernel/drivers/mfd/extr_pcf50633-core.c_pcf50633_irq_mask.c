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
struct pcf50633 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int __pcf50633_irq_mask_set (struct pcf50633*,int,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 

int pcf50633_irq_mask(struct pcf50633 *pcf, int irq)
{
	dev_info(pcf->dev, "Masking IRQ %d\n", irq);

	return __pcf50633_irq_mask_set(pcf, irq, 1);
}