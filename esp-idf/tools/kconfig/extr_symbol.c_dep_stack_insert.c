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
struct symbol {int dummy; } ;
struct dep_stack {struct symbol* sym; struct dep_stack* prev; struct dep_stack* next; } ;

/* Variables and functions */
 struct dep_stack* check_top ; 
 int /*<<< orphan*/  memset (struct dep_stack*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dep_stack_insert(struct dep_stack *stack, struct symbol *sym)
{
	memset(stack, 0, sizeof(*stack));
	if (check_top)
		check_top->next = stack;
	stack->prev = check_top;
	stack->sym = sym;
	check_top = stack;
}