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
typedef  int /*<<< orphan*/  act2000_card ;

/* Variables and functions */
 int /*<<< orphan*/  ISA_PORT_SIS ; 
 int /*<<< orphan*/  ISA_SIS_INT ; 
 int /*<<< orphan*/  act2000_isa_select_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
act2000_isa_enable_irq(act2000_card * card)
{
	act2000_isa_select_irq(card);
	/* Enable READ irq */
	outb(ISA_SIS_INT, ISA_PORT_SIS);
}