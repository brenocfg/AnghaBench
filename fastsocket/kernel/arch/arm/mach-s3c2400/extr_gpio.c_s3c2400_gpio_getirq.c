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
 int EINVAL ; 
 unsigned int IRQ_EINT0 ; 
 unsigned int S3C2400_GPE (int) ; 
 unsigned int S3C2410_GPE (int /*<<< orphan*/ ) ; 

int s3c2400_gpio_getirq(unsigned int pin)
{
	if (pin < S3C2410_GPE(0) || pin > S3C2400_GPE(7))
		return -EINVAL;  /* not valid interrupts */

	return (pin - S3C2410_GPE(0)) + IRQ_EINT0;
}