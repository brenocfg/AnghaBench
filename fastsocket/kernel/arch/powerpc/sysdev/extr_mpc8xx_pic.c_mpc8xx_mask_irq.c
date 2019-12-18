#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ hwirq; } ;
struct TYPE_3__ {int /*<<< orphan*/  sc_simask; } ;

/* Variables and functions */
 TYPE_2__* irq_map ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 
 int* ppc_cached_irq_mask ; 
 TYPE_1__* siu_reg ; 

__attribute__((used)) static void mpc8xx_mask_irq(unsigned int virq)
{
	int	bit, word;
	unsigned int irq_nr = (unsigned int)irq_map[virq].hwirq;

	bit = irq_nr & 0x1f;
	word = irq_nr >> 5;

	ppc_cached_irq_mask[word] &= ~(1 << (31-bit));
	out_be32(&siu_reg->sc_simask, ppc_cached_irq_mask[word]);
}