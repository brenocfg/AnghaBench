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
struct irq_desc {int /*<<< orphan*/  status; TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* mask ) (unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_MASKED ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 

__attribute__((used)) static void default_shutdown(unsigned int irq)
{
	struct irq_desc *desc = irq_to_desc(irq);

	desc->chip->mask(irq);
	desc->status |= IRQ_MASKED;
}