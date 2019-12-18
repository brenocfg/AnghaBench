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
 int* IXP4XX_ICMR ; 
 int* IXP4XX_ICMR2 ; 
 scalar_t__ cpu_is_ixp43x () ; 
 scalar_t__ cpu_is_ixp46x () ; 
 int /*<<< orphan*/  ixp4xx_irq_ack (unsigned int) ; 
 int ixp4xx_irq_edge ; 

__attribute__((used)) static void ixp4xx_irq_unmask(unsigned int irq)
{
	if (!(ixp4xx_irq_edge & (1 << irq)))
		ixp4xx_irq_ack(irq);

	if ((cpu_is_ixp46x() || cpu_is_ixp43x()) && irq >= 32)
		*IXP4XX_ICMR2 |= (1 << (irq - 32));
	else
		*IXP4XX_ICMR |= (1 << irq);
}