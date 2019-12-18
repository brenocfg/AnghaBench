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
 int GEDR0 ; 
 unsigned int IRQ_GPIO0 ; 

__attribute__((used)) static void pxa_ack_low_gpio(unsigned int irq)
{
	GEDR0 = (1 << (irq - IRQ_GPIO0));
}