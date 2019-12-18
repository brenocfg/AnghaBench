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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  EMMA2RH_BHIF_SW_INT_EN ; 
 scalar_t__ EMMA2RH_SW_IRQ_BASE ; 
 int emma2rh_in32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emma2rh_out32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void emma2rh_sw_irq_enable(unsigned int irq)
{
	u32 reg;

	irq -= EMMA2RH_SW_IRQ_BASE;

	reg = emma2rh_in32(EMMA2RH_BHIF_SW_INT_EN);
	reg |= 1 << irq;
	emma2rh_out32(EMMA2RH_BHIF_SW_INT_EN, reg);
}