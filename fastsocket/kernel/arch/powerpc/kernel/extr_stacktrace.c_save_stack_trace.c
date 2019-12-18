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
struct stack_trace {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  save_context_stack (struct stack_trace*,unsigned long,int /*<<< orphan*/ ,int) ; 

void save_stack_trace(struct stack_trace *trace)
{
	unsigned long sp;

	asm("mr %0,1" : "=r" (sp));

	save_context_stack(trace, sp, current, 1);
}