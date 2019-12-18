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
struct module {int taints; } ;
struct kernel_symbol {int dummy; } ;
typedef  int /*<<< orphan*/  Elf_Shdr ;

/* Variables and functions */
 int TAINT_PROPRIETARY_MODULE ; 
 int /*<<< orphan*/  check_version (int /*<<< orphan*/ *,unsigned int,char const*,struct module*,unsigned long const*,struct module*) ; 
 struct kernel_symbol* find_symbol (char const*,struct module**,unsigned long const**,int,int) ; 
 int /*<<< orphan*/  use_module (struct module*,struct module*) ; 

__attribute__((used)) static const struct kernel_symbol *resolve_symbol(Elf_Shdr *sechdrs,
						  unsigned int versindex,
						  const char *name,
						  struct module *mod)
{
	struct module *owner;
	const struct kernel_symbol *sym;
	const unsigned long *crc;

	sym = find_symbol(name, &owner, &crc,
			  !(mod->taints & (1 << TAINT_PROPRIETARY_MODULE)), true);
	/* use_module can fail due to OOM,
	   or module initialization or unloading */
	if (sym) {
		if (!check_version(sechdrs, versindex, name, mod, crc, owner)
		    || !use_module(mod, owner))
			sym = NULL;
	}
	return sym;
}