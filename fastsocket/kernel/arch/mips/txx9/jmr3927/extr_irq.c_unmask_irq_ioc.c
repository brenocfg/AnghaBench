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
 int /*<<< orphan*/  JMR3927_IOC_INTM_ADDR ; 
 int /*<<< orphan*/  JMR3927_IOC_REV_ADDR ; 
 unsigned int JMR3927_IRQ_IOC ; 
 unsigned char jmr3927_ioc_reg_in (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jmr3927_ioc_reg_out (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unmask_irq_ioc(unsigned int irq)
{
	/* 0: mask */
	unsigned int irq_nr = irq - JMR3927_IRQ_IOC;
	unsigned char imask = jmr3927_ioc_reg_in(JMR3927_IOC_INTM_ADDR);
	unsigned int bit = 1 << irq_nr;
	jmr3927_ioc_reg_out(imask | bit, JMR3927_IOC_INTM_ADDR);
	/* flush write buffer */
	(void)jmr3927_ioc_reg_in(JMR3927_IOC_REV_ADDR);
}