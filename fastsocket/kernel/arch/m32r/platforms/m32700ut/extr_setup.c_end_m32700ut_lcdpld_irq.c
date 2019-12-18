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
 int /*<<< orphan*/  M32R_IRQ_INT2 ; 
 int /*<<< orphan*/  enable_m32700ut_lcdpld_irq (unsigned int) ; 
 int /*<<< orphan*/  end_m32700ut_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void end_m32700ut_lcdpld_irq(unsigned int irq)
{
	enable_m32700ut_lcdpld_irq(irq);
	end_m32700ut_irq(M32R_IRQ_INT2);
}