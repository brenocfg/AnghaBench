#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ccdc_csc {TYPE_1__* coeff; int /*<<< orphan*/  enable; } ;
struct TYPE_2__ {int integer; int decimal; } ;

/* Variables and functions */
 int CCDC_CSCM_MSB_SHIFT ; 
 int CCDC_CSC_COEFF_TABLE_SIZE ; 
 int CCDC_CSC_COEF_DECIMAL_MASK ; 
 int CCDC_CSC_COEF_INTEG_MASK ; 
 int CCDC_CSC_COEF_INTEG_SHIFT ; 
 int CCDC_CSC_DEC_MAX ; 
 int CCDC_CSC_ENABLE ; 
 scalar_t__ CSCCTL ; 
 scalar_t__ CSCM0 ; 
 int /*<<< orphan*/  regw (int,scalar_t__) ; 

__attribute__((used)) static void ccdc_config_csc(struct ccdc_csc *csc)
{
	u32 val1, val2;
	int i;

	if (!csc->enable)
		return;

	/* Enable the CSC sub-module */
	regw(CCDC_CSC_ENABLE, CSCCTL);

	/* Converting the co-eff as per the format of the register */
	for (i = 0; i < CCDC_CSC_COEFF_TABLE_SIZE; i++) {
		if ((i % 2) == 0) {
			/* CSCM - LSB */
			val1 = (csc->coeff[i].integer &
				CCDC_CSC_COEF_INTEG_MASK)
				<< CCDC_CSC_COEF_INTEG_SHIFT;
			/*
			 * convert decimal part to binary. Use 2 decimal
			 * precision, user values range from .00 - 0.99
			 */
			val1 |= (((csc->coeff[i].decimal &
				CCDC_CSC_COEF_DECIMAL_MASK) *
				CCDC_CSC_DEC_MAX) / 100);
		} else {

			/* CSCM - MSB */
			val2 = (csc->coeff[i].integer &
				CCDC_CSC_COEF_INTEG_MASK)
				<< CCDC_CSC_COEF_INTEG_SHIFT;
			val2 |= (((csc->coeff[i].decimal &
				 CCDC_CSC_COEF_DECIMAL_MASK) *
				 CCDC_CSC_DEC_MAX) / 100);
			val2 <<= CCDC_CSCM_MSB_SHIFT;
			val2 |= val1;
			regw(val2, (CSCM0 + ((i - 1) << 1)));
		}
	}
}