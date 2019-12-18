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
struct ucb1x00 {int dummy; } ;

/* Variables and functions */
 int NO_IRQ ; 
 int /*<<< orphan*/  UCB_ADC_CR ; 
 int /*<<< orphan*/  UCB_ADC_DATA ; 
 int UCB_ADC_DAT_VAL ; 
 int UCB_ADC_ENA ; 
 int UCB_ADC_START ; 
 int UCB_IE_ADC ; 
 int /*<<< orphan*/  UCB_IE_CLEAR ; 
 int /*<<< orphan*/  UCB_IE_FAL ; 
 int /*<<< orphan*/  UCB_IE_RIS ; 
 int probe_irq_off (unsigned long) ; 
 unsigned long probe_irq_on () ; 
 int ucb1x00_reg_read (struct ucb1x00*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucb1x00_reg_write (struct ucb1x00*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ucb1x00_detect_irq(struct ucb1x00 *ucb)
{
	unsigned long mask;

	mask = probe_irq_on();
	if (!mask) {
		probe_irq_off(mask);
		return NO_IRQ;
	}

	/*
	 * Enable the ADC interrupt.
	 */
	ucb1x00_reg_write(ucb, UCB_IE_RIS, UCB_IE_ADC);
	ucb1x00_reg_write(ucb, UCB_IE_FAL, UCB_IE_ADC);
	ucb1x00_reg_write(ucb, UCB_IE_CLEAR, 0xffff);
	ucb1x00_reg_write(ucb, UCB_IE_CLEAR, 0);

	/*
	 * Cause an ADC interrupt.
	 */
	ucb1x00_reg_write(ucb, UCB_ADC_CR, UCB_ADC_ENA);
	ucb1x00_reg_write(ucb, UCB_ADC_CR, UCB_ADC_ENA | UCB_ADC_START);

	/*
	 * Wait for the conversion to complete.
	 */
	while ((ucb1x00_reg_read(ucb, UCB_ADC_DATA) & UCB_ADC_DAT_VAL) == 0);
	ucb1x00_reg_write(ucb, UCB_ADC_CR, 0);

	/*
	 * Disable and clear interrupt.
	 */
	ucb1x00_reg_write(ucb, UCB_IE_RIS, 0);
	ucb1x00_reg_write(ucb, UCB_IE_FAL, 0);
	ucb1x00_reg_write(ucb, UCB_IE_CLEAR, 0xffff);
	ucb1x00_reg_write(ucb, UCB_IE_CLEAR, 0);

	/*
	 * Read triggered interrupt.
	 */
	return probe_irq_off(mask);
}