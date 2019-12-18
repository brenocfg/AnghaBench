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
 int* CIC_STS_REG ; 
 unsigned int MSP_CIC_INTBASE ; 
 unsigned int MSP_PER_INTBASE ; 
 int* PER_INT_STS_REG ; 
 int /*<<< orphan*/  mask_msp_cic_irq (unsigned int) ; 

__attribute__((used)) static inline void ack_msp_cic_irq(unsigned int irq)
{
	mask_msp_cic_irq(irq);

	/*
	 * only really necessary for 18, 16-14 and sometimes 3:0 (since
	 * these can be edge sensitive) but it doesn't hurt for the others.
	 */

	/* check for PER interrupt range */
	if (irq < MSP_PER_INTBASE)
		*CIC_STS_REG = (1 << (irq - MSP_CIC_INTBASE));
	else
		*PER_INT_STS_REG = (1 << (irq - MSP_PER_INTBASE));
}