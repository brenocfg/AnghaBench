#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct module {int dummy; } ;
struct TYPE_7__ {size_t e_shstrndx; unsigned int e_shnum; int e_flags; } ;
struct TYPE_6__ {int sh_offset; scalar_t__ sh_type; unsigned int sh_link; unsigned int sh_info; int sh_name; scalar_t__ sh_addr; } ;
typedef  TYPE_1__ Elf_Shdr ;
typedef  TYPE_2__ Elf_Ehdr ;

/* Variables and functions */
 int EF_BFIN_CODE_IN_L1 ; 
 int EF_BFIN_CODE_IN_L2 ; 
 int ENOEXEC ; 
 scalar_t__ SHT_RELA ; 
 scalar_t__ SHT_SYMTAB ; 
 long apply_relocate_add (TYPE_1__*,char const*,unsigned int,unsigned int,struct module*) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

int
module_finalize(const Elf_Ehdr * hdr,
		const Elf_Shdr * sechdrs, struct module *mod)
{
	unsigned int i, strindex = 0, symindex = 0;
	char *secstrings;
	long err = 0;

	secstrings = (void *)hdr + sechdrs[hdr->e_shstrndx].sh_offset;

	for (i = 1; i < hdr->e_shnum; i++) {
		/* Internal symbols and strings. */
		if (sechdrs[i].sh_type == SHT_SYMTAB) {
			symindex = i;
			strindex = sechdrs[i].sh_link;
		}
	}

	for (i = 1; i < hdr->e_shnum; i++) {
		const char *strtab = (char *)sechdrs[strindex].sh_addr;
		unsigned int info = sechdrs[i].sh_info;
		const char *shname = secstrings + sechdrs[i].sh_name;

		/* Not a valid relocation section? */
		if (info >= hdr->e_shnum)
			continue;

		/* Only support RELA relocation types */
		if (sechdrs[i].sh_type != SHT_RELA)
			continue;

		if (!strcmp(".rela.l2.text", shname) ||
		    !strcmp(".rela.l1.text", shname) ||
		    (!strcmp(".rela.text", shname) &&
			 (hdr->e_flags & (EF_BFIN_CODE_IN_L1 | EF_BFIN_CODE_IN_L2)))) {

			err = apply_relocate_add((Elf_Shdr *) sechdrs, strtab,
					   symindex, i, mod);
			if (err < 0)
				return -ENOEXEC;
		}
	}

	return 0;
}