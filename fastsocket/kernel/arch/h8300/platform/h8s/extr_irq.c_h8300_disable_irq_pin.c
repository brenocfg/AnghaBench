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
 unsigned int EXT_IRQ0 ; 
 unsigned int EXT_IRQ15 ; 
 int /*<<< orphan*/  H8300_GPIO_FREE (unsigned short,unsigned short) ; 
 scalar_t__ IER ; 
 int /*<<< orphan*/  IRQ_GPIO_MAP (unsigned short,unsigned int,unsigned short,unsigned short) ; 
 scalar_t__ ISR ; 

void h8300_disable_irq_pin(unsigned int irq)
{
	if (irq >= EXT_IRQ0 && irq <= EXT_IRQ15) {
		/* disable interrupt & release IRQ pin */
		unsigned short ptn = 1 << (irq - EXT_IRQ0);
		unsigned short port_no,bit_no;
		*(volatile unsigned short *)ISR &= ~ptn;
		*(volatile unsigned short *)IER &= ~ptn;
		IRQ_GPIO_MAP(ptn, irq, port_no, bit_no);
		H8300_GPIO_FREE(port_no, bit_no);
	}
}