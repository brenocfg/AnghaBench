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
struct irq_desc {TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable ) (unsigned int) ;} ;

/* Variables and functions */
 struct irq_desc* irq_to_desc (unsigned int) ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 

__attribute__((used)) static unsigned int default_startup(unsigned int irq)
{
	struct irq_desc *desc = irq_to_desc(irq);

	desc->chip->enable(irq);
	return 0;
}