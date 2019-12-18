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
typedef  int /*<<< orphan*/  ipipe_irq_handler_t ;

/* Variables and functions */
 int IPIPE_HANDLE_MASK ; 
 int IPIPE_PASS_MASK ; 
 unsigned int NR_IRQS ; 
 int /*<<< orphan*/  __ipipe_ack_irq ; 
 unsigned long __ipipe_core_clock ; 
 unsigned long __ipipe_freq_scale ; 
 int /*<<< orphan*/  asm_do_IRQ ; 
 unsigned long get_cclk () ; 
 int /*<<< orphan*/  ipipe_root_domain ; 
 int /*<<< orphan*/  ipipe_virtualize_irq (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void __ipipe_enable_pipeline(void)
{
	unsigned irq;

	__ipipe_core_clock = get_cclk(); /* Fetch this once. */
	__ipipe_freq_scale = 1000000000UL / __ipipe_core_clock;

	for (irq = 0; irq < NR_IRQS; ++irq)
		ipipe_virtualize_irq(ipipe_root_domain,
				     irq,
				     (ipipe_irq_handler_t)&asm_do_IRQ,
				     NULL,
				     &__ipipe_ack_irq,
				     IPIPE_HANDLE_MASK | IPIPE_PASS_MASK);
}