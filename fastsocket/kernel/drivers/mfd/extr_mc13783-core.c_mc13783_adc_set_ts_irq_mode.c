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
struct mc13783 {int dummy; } ;

/* Variables and functions */
 unsigned int MC13783_ADC0_ADREFEN ; 
 unsigned int MC13783_ADC0_ADREFMODE ; 
 unsigned int MC13783_ADC0_TSMOD0 ; 
 unsigned int MC13783_ADC1_ADEN ; 
 unsigned int MC13783_ADC1_ADTRIGIGN ; 
 int /*<<< orphan*/  MC13783_REG_ADC_0 ; 
 int /*<<< orphan*/  MC13783_REG_ADC_1 ; 
 int /*<<< orphan*/  mc13783_reg_write (struct mc13783*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void mc13783_adc_set_ts_irq_mode(struct mc13783 *mc13783)
{
	unsigned int reg_adc0, reg_adc1;

	reg_adc0 = MC13783_ADC0_ADREFEN | MC13783_ADC0_ADREFMODE
			| MC13783_ADC0_TSMOD0;
	reg_adc1 = MC13783_ADC1_ADEN | MC13783_ADC1_ADTRIGIGN;

	mc13783_reg_write(mc13783, MC13783_REG_ADC_0, reg_adc0);
	mc13783_reg_write(mc13783, MC13783_REG_ADC_1, reg_adc1);
}