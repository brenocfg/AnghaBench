#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* sec_core_text; TYPE_2__* sec_devinit_text; TYPE_2__* sec_init_text; TYPE_2__* unw_sec_core; TYPE_2__* unw_sec_devinit; TYPE_2__* unw_sec_init; } ;
struct module {TYPE_1__ arch; } ;
struct TYPE_8__ {int e_shnum; } ;
struct TYPE_7__ {int sh_name; } ;
typedef  TYPE_2__ Elf_Shdr ;
typedef  TYPE_3__ Elf_Ehdr ;

/* Variables and functions */
 scalar_t__ strcmp (char*,char*) ; 

int module_frob_arch_sections(Elf_Ehdr *hdr,
			      Elf_Shdr *sechdrs,
			      char *secstrings,
			      struct module *mod)
{
#ifdef CONFIG_ARM_UNWIND
	Elf_Shdr *s, *sechdrs_end = sechdrs + hdr->e_shnum;

	for (s = sechdrs; s < sechdrs_end; s++) {
		if (strcmp(".ARM.exidx.init.text", secstrings + s->sh_name) == 0)
			mod->arch.unw_sec_init = s;
		else if (strcmp(".ARM.exidx.devinit.text", secstrings + s->sh_name) == 0)
			mod->arch.unw_sec_devinit = s;
		else if (strcmp(".ARM.exidx", secstrings + s->sh_name) == 0)
			mod->arch.unw_sec_core = s;
		else if (strcmp(".init.text", secstrings + s->sh_name) == 0)
			mod->arch.sec_init_text = s;
		else if (strcmp(".devinit.text", secstrings + s->sh_name) == 0)
			mod->arch.sec_devinit_text = s;
		else if (strcmp(".text", secstrings + s->sh_name) == 0)
			mod->arch.sec_core_text = s;
	}
#endif
	return 0;
}