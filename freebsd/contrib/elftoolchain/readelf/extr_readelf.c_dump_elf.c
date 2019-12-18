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
struct TYPE_2__ {scalar_t__* e_ident; } ;
struct readelf {int options; int /*<<< orphan*/  dw_decode; int /*<<< orphan*/  dw_read; TYPE_1__ ehdr; int /*<<< orphan*/  elf; int /*<<< orphan*/  ec; } ;

/* Variables and functions */
 size_t EI_DATA ; 
 int /*<<< orphan*/  ELFCLASSNONE ; 
 scalar_t__ ELFDATA2MSB ; 
 int RE_AA ; 
 int RE_D ; 
 int RE_G ; 
 int RE_H ; 
 int RE_II ; 
 int RE_L ; 
 int RE_N ; 
 int RE_P ; 
 int RE_R ; 
 int RE_S ; 
 int RE_SS ; 
 int RE_VV ; 
 int RE_W ; 
 int RE_X ; 
 int /*<<< orphan*/  _decode_lsb ; 
 int /*<<< orphan*/  _decode_msb ; 
 int /*<<< orphan*/  _read_lsb ; 
 int /*<<< orphan*/  _read_msb ; 
 int /*<<< orphan*/  dump_arch_specific_info (struct readelf*) ; 
 int /*<<< orphan*/  dump_dwarf (struct readelf*) ; 
 int /*<<< orphan*/  dump_dynamic (struct readelf*) ; 
 int /*<<< orphan*/  dump_ehdr (struct readelf*) ; 
 int /*<<< orphan*/  dump_hash (struct readelf*) ; 
 int /*<<< orphan*/  dump_notes (struct readelf*) ; 
 int /*<<< orphan*/  dump_phdr (struct readelf*) ; 
 int /*<<< orphan*/  dump_reloc (struct readelf*) ; 
 int /*<<< orphan*/  dump_section_groups (struct readelf*) ; 
 int /*<<< orphan*/  dump_shdr (struct readelf*) ; 
 int /*<<< orphan*/  dump_symtabs (struct readelf*) ; 
 int /*<<< orphan*/  dump_ver (struct readelf*) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int /*<<< orphan*/  gelf_getclass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gelf_getehdr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  hex_dump (struct readelf*) ; 
 int /*<<< orphan*/  load_sections (struct readelf*) ; 
 int /*<<< orphan*/  search_ver (struct readelf*) ; 
 int /*<<< orphan*/  str_dump (struct readelf*) ; 
 int /*<<< orphan*/  unload_sections (struct readelf*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_elf(struct readelf *re)
{

	/* Fetch ELF header. No need to continue if it fails. */
	if (gelf_getehdr(re->elf, &re->ehdr) == NULL) {
		warnx("gelf_getehdr failed: %s", elf_errmsg(-1));
		return;
	}
	if ((re->ec = gelf_getclass(re->elf)) == ELFCLASSNONE) {
		warnx("gelf_getclass failed: %s", elf_errmsg(-1));
		return;
	}
	if (re->ehdr.e_ident[EI_DATA] == ELFDATA2MSB) {
		re->dw_read = _read_msb;
		re->dw_decode = _decode_msb;
	} else {
		re->dw_read = _read_lsb;
		re->dw_decode = _decode_lsb;
	}

	if (re->options & ~RE_H)
		load_sections(re);
	if ((re->options & RE_VV) || (re->options & RE_S))
		search_ver(re);
	if (re->options & RE_H)
		dump_ehdr(re);
	if (re->options & RE_L)
		dump_phdr(re);
	if (re->options & RE_SS)
		dump_shdr(re);
	if (re->options & RE_G)
		dump_section_groups(re);
	if (re->options & RE_D)
		dump_dynamic(re);
	if (re->options & RE_R)
		dump_reloc(re);
	if (re->options & RE_S)
		dump_symtabs(re);
	if (re->options & RE_N)
		dump_notes(re);
	if (re->options & RE_II)
		dump_hash(re);
	if (re->options & RE_X)
		hex_dump(re);
	if (re->options & RE_P)
		str_dump(re);
	if (re->options & RE_VV)
		dump_ver(re);
	if (re->options & RE_AA)
		dump_arch_specific_info(re);
	if (re->options & RE_W)
		dump_dwarf(re);
	if (re->options & ~RE_H)
		unload_sections(re);
}