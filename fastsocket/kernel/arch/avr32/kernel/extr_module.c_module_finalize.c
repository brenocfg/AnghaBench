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
struct TYPE_2__ {int /*<<< orphan*/ * syminfo; } ;
struct module {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  Elf_Shdr ;
typedef  int /*<<< orphan*/  Elf_Ehdr ;

/* Variables and functions */
 int module_bug_finalize (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,struct module*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

int module_finalize(const Elf_Ehdr *hdr, const Elf_Shdr *sechdrs,
		    struct module *module)
{
	vfree(module->arch.syminfo);
	module->arch.syminfo = NULL;

	return module_bug_finalize(hdr, sechdrs, module);
}