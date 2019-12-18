#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {scalar_t__ sh_type; size_t sh_size; size_t sh_entsize; int /*<<< orphan*/  sh_link; } ;
struct TYPE_5__ {int /*<<< orphan*/  st_name; int /*<<< orphan*/  st_info; } ;
typedef  TYPE_1__ GElf_Sym ;
typedef  TYPE_2__ GElf_Shdr ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  int /*<<< orphan*/  Elf_Data ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ GELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ SHT_SYMTAB ; 
 scalar_t__ STT_FUNC ; 
 scalar_t__ STT_OBJECT ; 
 scalar_t__ STT_TLS ; 
 int /*<<< orphan*/ * elf_getdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * elf_nextscn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* elf_strptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gelf_getshdr (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  gelf_getsym (int /*<<< orphan*/ *,size_t,TYPE_1__*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  terminate (char*) ; 

__attribute__((used)) static boolean_t
should_have_dwarf(Elf *elf)
{
	Elf_Scn *scn = NULL;
	Elf_Data *data = NULL;
	GElf_Shdr shdr;
	GElf_Sym sym;
	uint32_t symdx = 0;
	size_t nsyms = 0;
	boolean_t found = B_FALSE;

	while ((scn = elf_nextscn(elf, scn)) != NULL) {
		gelf_getshdr(scn, &shdr);

		if (shdr.sh_type == SHT_SYMTAB) {
			found = B_TRUE;
			break;
		}
	}

	if (!found)
		terminate("cannot convert stripped objects\n");

	data = elf_getdata(scn, NULL);
	nsyms = shdr.sh_size / shdr.sh_entsize;

	for (symdx = 0; symdx < nsyms; symdx++) {
		gelf_getsym(data, symdx, &sym);

		if ((GELF_ST_TYPE(sym.st_info) == STT_FUNC) ||
		    (GELF_ST_TYPE(sym.st_info) == STT_TLS) ||
		    (GELF_ST_TYPE(sym.st_info) == STT_OBJECT)) {
			char *name;

			name = elf_strptr(elf, shdr.sh_link, sym.st_name);

			/* Studio emits these local symbols regardless */
			if ((strcmp(name, "Bbss.bss") != 0) &&
			    (strcmp(name, "Ttbss.bss") != 0) &&
			    (strcmp(name, "Ddata.data") != 0) &&
			    (strcmp(name, "Ttdata.data") != 0) &&
			    (strcmp(name, "Drodata.rodata") != 0))
				return (B_TRUE);
		}
	}

	return (B_FALSE);
}