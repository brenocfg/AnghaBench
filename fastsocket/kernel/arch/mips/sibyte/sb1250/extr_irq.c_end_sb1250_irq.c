#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int status; } ;

/* Variables and functions */
 int IRQ_DISABLED ; 
 int IRQ_INPROGRESS ; 
 TYPE_1__* irq_desc ; 
 int /*<<< orphan*/ * sb1250_irq_owner ; 
 int /*<<< orphan*/  sb1250_unmask_irq (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void end_sb1250_irq(unsigned int irq)
{
	if (!(irq_desc[irq].status & (IRQ_DISABLED | IRQ_INPROGRESS))) {
		sb1250_unmask_irq(sb1250_irq_owner[irq], irq);
	}
}