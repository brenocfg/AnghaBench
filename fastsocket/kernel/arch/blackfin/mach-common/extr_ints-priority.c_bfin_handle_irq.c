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
struct irq_desc {int /*<<< orphan*/  (* handle_irq ) (unsigned int,struct irq_desc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __ipipe_handle_irq (unsigned int,struct pt_regs*) ; 
 int /*<<< orphan*/  ipipe_trace_irq_entry (unsigned int) ; 
 int /*<<< orphan*/  ipipe_trace_irq_exit (unsigned int) ; 
 struct irq_desc* irq_desc ; 
 int /*<<< orphan*/  stub1 (unsigned int,struct irq_desc*) ; 

__attribute__((used)) static void bfin_handle_irq(unsigned irq)
{
#ifdef CONFIG_IPIPE
	struct pt_regs regs;    /* Contents not used. */
	ipipe_trace_irq_entry(irq);
	__ipipe_handle_irq(irq, &regs);
	ipipe_trace_irq_exit(irq);
#else /* !CONFIG_IPIPE */
	struct irq_desc *desc = irq_desc + irq;
	desc->handle_irq(irq, desc);
#endif  /* !CONFIG_IPIPE */
}