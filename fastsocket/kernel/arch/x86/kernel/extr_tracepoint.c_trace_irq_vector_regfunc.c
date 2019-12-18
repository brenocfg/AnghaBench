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
 int /*<<< orphan*/  irq_vector_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_trace_idt_ctr (int) ; 
 int /*<<< orphan*/  smp_call_function (int /*<<< orphan*/  (*) (int /*<<< orphan*/ *),int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  switch_idt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_irq_vector_refcount ; 

void trace_irq_vector_regfunc(void)
{
	mutex_lock(&irq_vector_mutex);
	if (!trace_irq_vector_refcount) {
		set_trace_idt_ctr(1);
		smp_call_function(switch_idt, NULL, 0);
		switch_idt(NULL);
	}
	trace_irq_vector_refcount++;
	mutex_unlock(&irq_vector_mutex);
}