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
struct eic {unsigned int first_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICR ; 
 int /*<<< orphan*/  IDR ; 
 int /*<<< orphan*/  eic_writel (struct eic*,int /*<<< orphan*/ ,int) ; 
 struct eic* get_irq_chip_data (unsigned int) ; 

__attribute__((used)) static void eic_mask_ack_irq(unsigned int irq)
{
	struct eic *eic = get_irq_chip_data(irq);
	eic_writel(eic, ICR, 1 << (irq - eic->first_irq));
	eic_writel(eic, IDR, 1 << (irq - eic->first_irq));
}