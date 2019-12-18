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
 int /*<<< orphan*/  EXT_ENABLE_REG ; 
 int /*<<< orphan*/  KEY_IRQ_ENABLE_REG ; 
 scalar_t__ UART_IER ; 
 int /*<<< orphan*/  master_outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned int* serports ; 

__attribute__((used)) static void q40_disable_irqs(void)
{
	unsigned i, j;

	j = 0;
	while ((i = serports[j++]))
		outb(0, i + UART_IER);
	master_outb(0, EXT_ENABLE_REG);
	master_outb(0, KEY_IRQ_ENABLE_REG);
}