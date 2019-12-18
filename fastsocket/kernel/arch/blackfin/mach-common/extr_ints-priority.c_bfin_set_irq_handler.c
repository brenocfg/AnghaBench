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
struct irq_desc {int /*<<< orphan*/  handle_irq; } ;
typedef  int /*<<< orphan*/  irq_flow_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  _set_irq_handler (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_level_irq ; 
 struct irq_desc* irq_desc ; 

__attribute__((used)) static inline void bfin_set_irq_handler(unsigned irq, irq_flow_handler_t handle)
{
#ifdef CONFIG_IPIPE
	_set_irq_handler(irq, handle_level_irq);
#else
	struct irq_desc *desc = irq_desc + irq;
	/* May not call generic set_irq_handler() due to spinlock
	   recursion. */
	desc->handle_irq = handle;
#endif
}