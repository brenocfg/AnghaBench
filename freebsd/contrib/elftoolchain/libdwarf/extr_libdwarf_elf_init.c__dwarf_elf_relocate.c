#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* ed_data; int /*<<< orphan*/ * ed_alloc; } ;
struct TYPE_10__ {int /*<<< orphan*/ * e_ident; } ;
struct TYPE_9__ {scalar_t__ sh_type; scalar_t__ sh_size; size_t sh_info; size_t sh_link; } ;
struct TYPE_8__ {int /*<<< orphan*/  d_size; int /*<<< orphan*/  d_buf; } ;
typedef  TYPE_2__ GElf_Shdr ;
typedef  TYPE_3__ GElf_Ehdr ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  int /*<<< orphan*/  Elf_Data ;
typedef  int /*<<< orphan*/  Elf ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_4__ Dwarf_Elf_Data ;
typedef  int /*<<< orphan*/  Dwarf_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ELF_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int DW_DLE_ELF ; 
 int DW_DLE_MEMORY ; 
 int DW_DLE_NONE ; 
 size_t EI_DATA ; 
 scalar_t__ SHT_REL ; 
 scalar_t__ SHT_RELA ; 
 int /*<<< orphan*/  _DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  _dwarf_elf_apply_rel_reloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _dwarf_elf_apply_rela_reloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int elf_errno () ; 
 int /*<<< orphan*/ * elf_getdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * elf_nextscn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gelf_getehdr (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * gelf_getshdr (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_dwarf_elf_relocate(Dwarf_Debug dbg, Elf *elf, Dwarf_Elf_Data *ed, size_t shndx,
    size_t symtab, Elf_Data *symtab_data, Dwarf_Error *error)
{
	GElf_Ehdr eh;
	GElf_Shdr sh;
	Elf_Scn *scn;
	Elf_Data *rel;
	int elferr;

	if (symtab == 0 || symtab_data == NULL)
		return (DW_DLE_NONE);

	if (gelf_getehdr(elf, &eh) == NULL) {
		DWARF_SET_ELF_ERROR(dbg, error);
		return (DW_DLE_ELF);
	}

	scn = NULL;
	(void) elf_errno();
	while ((scn = elf_nextscn(elf, scn)) != NULL) {
		if (gelf_getshdr(scn, &sh) == NULL) {
			DWARF_SET_ELF_ERROR(dbg, error);
			return (DW_DLE_ELF);
		}

		if ((sh.sh_type != SHT_REL && sh.sh_type != SHT_RELA) ||
		     sh.sh_size == 0)
			continue;

		if (sh.sh_info == shndx && sh.sh_link == symtab) {
			if ((rel = elf_getdata(scn, NULL)) == NULL) {
				elferr = elf_errno();
				if (elferr != 0) {
					_DWARF_SET_ERROR(NULL, error,
					    DW_DLE_ELF, elferr);
					return (DW_DLE_ELF);
				} else
					return (DW_DLE_NONE);
			}

			ed->ed_alloc = malloc(ed->ed_data->d_size);
			if (ed->ed_alloc == NULL) {
				DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
				return (DW_DLE_MEMORY);
			}
			memcpy(ed->ed_alloc, ed->ed_data->d_buf,
			    ed->ed_data->d_size);
			if (sh.sh_type == SHT_REL)
				_dwarf_elf_apply_rel_reloc(dbg,
				    ed->ed_alloc, ed->ed_data->d_size,
				    rel, symtab_data, eh.e_ident[EI_DATA]);
			else
				_dwarf_elf_apply_rela_reloc(dbg,
				    ed->ed_alloc, ed->ed_data->d_size,
				    rel, symtab_data, eh.e_ident[EI_DATA]);

			return (DW_DLE_NONE);
		}
	}
	elferr = elf_errno();
	if (elferr != 0) {
		DWARF_SET_ELF_ERROR(dbg, error);
		return (DW_DLE_ELF);
	}

	return (DW_DLE_NONE);
}