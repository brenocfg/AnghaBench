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
 unsigned int PCM027_IRQ (int /*<<< orphan*/ ) ; 
 int PCM990_INTMSKENA ; 
 int PCM990_INTSETCLR ; 
 int pcm990_irq_enabled ; 

__attribute__((used)) static void pcm990_unmask_irq(unsigned int irq)
{
	int pcm990_irq = (irq - PCM027_IRQ(0));
	/* the irq can be acknowledged only if deasserted, so it's done here */
	PCM990_INTSETCLR |= 1 << pcm990_irq;
	PCM990_INTMSKENA  = (pcm990_irq_enabled |= (1 << pcm990_irq));
}