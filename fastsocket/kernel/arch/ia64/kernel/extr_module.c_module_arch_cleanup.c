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
struct TYPE_2__ {scalar_t__ core_unw_table; scalar_t__ init_unw_table; } ;
struct module {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  unw_remove_unwind_table (scalar_t__) ; 

void
module_arch_cleanup (struct module *mod)
{
	if (mod->arch.init_unw_table)
		unw_remove_unwind_table(mod->arch.init_unw_table);
	if (mod->arch.core_unw_table)
		unw_remove_unwind_table(mod->arch.core_unw_table);
}