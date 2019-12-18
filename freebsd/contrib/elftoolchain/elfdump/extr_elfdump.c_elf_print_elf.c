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
struct elfdump {int options; int /*<<< orphan*/  elf; int /*<<< orphan*/  ec; int /*<<< orphan*/  ehdr; } ;

/* Variables and functions */
 int ED_CHECKSUM ; 
 int ED_DYN ; 
 int ED_EHDR ; 
 int ED_GOT ; 
 int ED_HASH ; 
 int ED_INTERP ; 
 int ED_NOTE ; 
 int ED_PHDR ; 
 int ED_REL ; 
 int ED_SHDR ; 
 int ED_SYMTAB ; 
 int ED_SYMVER ; 
 int /*<<< orphan*/  ELFCLASSNONE ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int /*<<< orphan*/  elf_print_checksum (struct elfdump*) ; 
 int /*<<< orphan*/  elf_print_dynamic (struct elfdump*) ; 
 int /*<<< orphan*/  elf_print_ehdr (struct elfdump*) ; 
 int /*<<< orphan*/  elf_print_got (struct elfdump*) ; 
 int /*<<< orphan*/  elf_print_hash (struct elfdump*) ; 
 int /*<<< orphan*/  elf_print_interp (struct elfdump*) ; 
 int /*<<< orphan*/  elf_print_note (struct elfdump*) ; 
 int /*<<< orphan*/  elf_print_phdr (struct elfdump*) ; 
 int /*<<< orphan*/  elf_print_reloc (struct elfdump*) ; 
 int /*<<< orphan*/  elf_print_shdr (struct elfdump*) ; 
 int /*<<< orphan*/  elf_print_symtabs (struct elfdump*) ; 
 int /*<<< orphan*/  elf_print_symver (struct elfdump*) ; 
 int /*<<< orphan*/  gelf_getclass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gelf_getehdr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_sections (struct elfdump*) ; 
 int /*<<< orphan*/  unload_sections (struct elfdump*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
elf_print_elf(struct elfdump *ed)
{

	if (gelf_getehdr(ed->elf, &ed->ehdr) == NULL) {
		warnx("gelf_getehdr failed: %s", elf_errmsg(-1));
		return;
	}
	if ((ed->ec = gelf_getclass(ed->elf)) == ELFCLASSNONE) {
		warnx("gelf_getclass failed: %s", elf_errmsg(-1));
		return;
	}

	if (ed->options & (ED_SHDR | ED_DYN | ED_REL | ED_GOT | ED_SYMTAB |
	    ED_SYMVER | ED_NOTE | ED_HASH))
		load_sections(ed);

	if (ed->options & ED_EHDR)
		elf_print_ehdr(ed);
	if (ed->options & ED_PHDR)
		elf_print_phdr(ed);
	if (ed->options & ED_INTERP)
		elf_print_interp(ed);
	if (ed->options & ED_SHDR)
		elf_print_shdr(ed);
	if (ed->options & ED_DYN)
		elf_print_dynamic(ed);
	if (ed->options & ED_REL)
		elf_print_reloc(ed);
	if (ed->options & ED_GOT)
		elf_print_got(ed);
	if (ed->options & ED_SYMTAB)
		elf_print_symtabs(ed);
	if (ed->options & ED_SYMVER)
		elf_print_symver(ed);
	if (ed->options & ED_NOTE)
		elf_print_note(ed);
	if (ed->options & ED_HASH)
		elf_print_hash(ed);
	if (ed->options & ED_CHECKSUM)
		elf_print_checksum(ed);

	unload_sections(ed);
}