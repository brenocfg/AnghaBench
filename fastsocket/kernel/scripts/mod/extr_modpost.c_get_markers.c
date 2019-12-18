#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct module {char** markers; size_t nmarkers; int /*<<< orphan*/  name; } ;
struct elf_info {size_t markers_strings_sec; scalar_t__ strtab; TYPE_1__ const* symtab_stop; TYPE_1__* symtab_start; scalar_t__ hdr; TYPE_2__* sechdrs; } ;
struct TYPE_4__ {int sh_offset; } ;
struct TYPE_3__ {scalar_t__ st_shndx; int st_value; scalar_t__ st_name; int /*<<< orphan*/  st_info; } ;
typedef  TYPE_1__ Elf_Sym ;
typedef  TYPE_2__ Elf_Shdr ;

/* Variables and functions */
 scalar_t__ ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 char** NOFAIL (char*) ; 
 scalar_t__ STT_OBJECT ; 
 int /*<<< orphan*/  asprintf (char**,char*,char const*,int /*<<< orphan*/ ,char const*) ; 
 char* malloc (int) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strncmp (scalar_t__,char*,int) ; 

__attribute__((used)) static void get_markers(struct elf_info *info, struct module *mod)
{
	const Elf_Shdr *sh = &info->sechdrs[info->markers_strings_sec];
	const char *strings = (const char *) info->hdr + sh->sh_offset;
	const Elf_Sym *sym, *first_sym, *last_sym;
	size_t n;

	if (!info->markers_strings_sec)
		return;

	/*
	 * First count the strings.  We look for all the symbols defined
	 * in the __markers_strings section named __mstrtab_*.  For
	 * these local names, the compiler puts a random .NNN suffix on,
	 * so the names don't correspond exactly.
	 */
	first_sym = last_sym = NULL;
	n = 0;
	for (sym = info->symtab_start; sym < info->symtab_stop; sym++)
		if (ELF_ST_TYPE(sym->st_info) == STT_OBJECT &&
		    sym->st_shndx == info->markers_strings_sec &&
		    !strncmp(info->strtab + sym->st_name,
			     "__mstrtab_", sizeof "__mstrtab_" - 1)) {
			if (first_sym == NULL)
				first_sym = sym;
			last_sym = sym;
			++n;
		}

	if (n == 0)
		return;

	/*
	 * Now collect each name and format into a line for the output.
	 * Lines look like:
	 *	marker_name	vmlinux	marker %s format %d
	 * The format string after the second \t can use whitespace.
	 */
	mod->markers = NOFAIL(malloc(sizeof mod->markers[0] * n));
	mod->nmarkers = n;

	n = 0;
	for (sym = first_sym; sym <= last_sym; sym++)
		if (ELF_ST_TYPE(sym->st_info) == STT_OBJECT &&
		    sym->st_shndx == info->markers_strings_sec &&
		    !strncmp(info->strtab + sym->st_name,
			     "__mstrtab_", sizeof "__mstrtab_" - 1)) {
			const char *name = strings + sym->st_value;
			const char *fmt = strchr(name, '\0') + 1;
			char *line = NULL;
			asprintf(&line, "%s\t%s\t%s\n", name, mod->name, fmt);
			NOFAIL(line);
			mod->markers[n++] = line;
		}
}