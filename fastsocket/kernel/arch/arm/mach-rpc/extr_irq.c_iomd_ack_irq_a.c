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
 int /*<<< orphan*/  IOMD_IRQCLRA ; 
 int /*<<< orphan*/  IOMD_IRQMASKA ; 
 unsigned int iomd_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iomd_writeb (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iomd_ack_irq_a(unsigned int irq)
{
	unsigned int val, mask;

	mask = 1 << irq;
	val = iomd_readb(IOMD_IRQMASKA);
	iomd_writeb(val & ~mask, IOMD_IRQMASKA);
	iomd_writeb(mask, IOMD_IRQCLRA);
}