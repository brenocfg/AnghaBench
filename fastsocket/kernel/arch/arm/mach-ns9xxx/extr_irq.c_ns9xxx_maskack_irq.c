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
 int /*<<< orphan*/  ns9xxx_ack_irq (unsigned int) ; 
 int /*<<< orphan*/  ns9xxx_mask_irq (unsigned int) ; 

__attribute__((used)) static void ns9xxx_maskack_irq(unsigned int irq)
{
	ns9xxx_mask_irq(irq);
	ns9xxx_ack_irq(irq);
}