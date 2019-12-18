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
struct module {int dummy; } ;
struct kernel_symbol {scalar_t__ value; } ;

/* Variables and functions */
 struct kernel_symbol* find_symbol (char const*,struct module**,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 scalar_t__ strong_try_module_get (struct module*) ; 

void *__symbol_get(const char *symbol)
{
	struct module *owner;
	const struct kernel_symbol *sym;

	preempt_disable();
	sym = find_symbol(symbol, &owner, NULL, true, true);
	if (sym && strong_try_module_get(owner))
		sym = NULL;
	preempt_enable();

	return sym ? (void *)sym->value : NULL;
}