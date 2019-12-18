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
 unsigned int IRQ_AUTO_7 ; 
 size_t IRQ_USER ; 
 unsigned int VEC_SPUR ; 
 int /*<<< orphan*/  bad_inthandler ; 
 size_t m68k_first_user_vec ; 
 int /*<<< orphan*/ * vectors ; 

void m68k_irq_shutdown(unsigned int irq)
{
	if (irq <= IRQ_AUTO_7)
		vectors[VEC_SPUR + irq] = bad_inthandler;
	else
		vectors[m68k_first_user_vec + irq - IRQ_USER] = bad_inthandler;
}