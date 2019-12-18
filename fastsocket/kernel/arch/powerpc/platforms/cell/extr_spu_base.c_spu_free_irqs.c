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
struct spu {scalar_t__* irqs; } ;

/* Variables and functions */
 scalar_t__ NO_IRQ ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct spu*) ; 

__attribute__((used)) static void spu_free_irqs(struct spu *spu)
{
	if (spu->irqs[0] != NO_IRQ)
		free_irq(spu->irqs[0], spu);
	if (spu->irqs[1] != NO_IRQ)
		free_irq(spu->irqs[1], spu);
	if (spu->irqs[2] != NO_IRQ)
		free_irq(spu->irqs[2], spu);
}