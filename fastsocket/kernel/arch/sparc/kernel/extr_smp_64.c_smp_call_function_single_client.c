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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_softint (int) ; 
 int /*<<< orphan*/  generic_smp_call_function_single_interrupt () ; 

void smp_call_function_single_client(int irq, struct pt_regs *regs)
{
	clear_softint(1 << irq);
	generic_smp_call_function_single_interrupt();
}