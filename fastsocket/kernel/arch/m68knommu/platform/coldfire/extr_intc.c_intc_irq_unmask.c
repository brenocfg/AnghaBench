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
 int /*<<< orphan*/  mcf_clrimr (scalar_t__) ; 
 scalar_t__* mcf_irq2imr ; 

__attribute__((used)) static void intc_irq_unmask(unsigned int irq)
{
	if (mcf_irq2imr[irq])
		mcf_clrimr(mcf_irq2imr[irq]);
}