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
struct module {int /*<<< orphan*/  core_text_size; int /*<<< orphan*/  module_core; int /*<<< orphan*/  init_text_size; int /*<<< orphan*/  module_init; } ;

/* Variables and functions */
 struct module* __module_address (unsigned long) ; 
 int /*<<< orphan*/  within (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct module *__module_text_address(unsigned long addr)
{
	struct module *mod = __module_address(addr);
	if (mod) {
		/* Make sure it's within the text section. */
		if (!within(addr, mod->module_init, mod->init_text_size)
		    && !within(addr, mod->module_core, mod->core_text_size))
			mod = NULL;
	}
	return mod;
}