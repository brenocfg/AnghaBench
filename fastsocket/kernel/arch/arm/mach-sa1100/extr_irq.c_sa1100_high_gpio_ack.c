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
 unsigned int GEDR ; 
 unsigned int GPIO11_27_MASK (unsigned int) ; 

__attribute__((used)) static void sa1100_high_gpio_ack(unsigned int irq)
{
	unsigned int mask = GPIO11_27_MASK(irq);

	GEDR = mask;
}