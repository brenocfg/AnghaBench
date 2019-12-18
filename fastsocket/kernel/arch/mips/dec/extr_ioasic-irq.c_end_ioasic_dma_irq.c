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
 int /*<<< orphan*/  clear_ioasic_irq (unsigned int) ; 
 int /*<<< orphan*/  end_ioasic_irq (unsigned int) ; 
 int /*<<< orphan*/  fast_iob () ; 

__attribute__((used)) static inline void end_ioasic_dma_irq(unsigned int irq)
{
	clear_ioasic_irq(irq);
	fast_iob();
	end_ioasic_irq(irq);
}