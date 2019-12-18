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
 int /*<<< orphan*/  intctl1_write (int) ; 
 int iop33x_mask1 ; 

__attribute__((used)) static void
iop33x_irq_mask2 (unsigned int irq)
{
	iop33x_mask1 &= ~(1 << (irq - 32));
	intctl1_write(iop33x_mask1);
}