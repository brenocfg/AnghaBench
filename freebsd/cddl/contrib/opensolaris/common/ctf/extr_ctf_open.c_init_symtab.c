#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ushort_t ;
typedef  int uint_t ;
typedef  int /*<<< orphan*/  uchar_t ;
struct TYPE_13__ {int cts_entsize; scalar_t__ cts_size; int /*<<< orphan*/ * cts_data; } ;
typedef  TYPE_1__ ctf_sect_t ;
struct TYPE_14__ {int cth_objtoff; int cth_funcoff; int cth_typeoff; } ;
typedef  TYPE_2__ ctf_header_t ;
struct TYPE_15__ {int* ctf_sxlate; int ctf_nsyms; scalar_t__ ctf_buf; } ;
typedef  TYPE_3__ ctf_file_t ;
struct TYPE_16__ {scalar_t__ st_name; scalar_t__ st_shndx; int /*<<< orphan*/  st_value; int /*<<< orphan*/  st_info; } ;
typedef  TYPE_4__ Elf64_Sym ;
typedef  int /*<<< orphan*/  Elf32_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_K_UNKNOWN ; 
 int ELF64_ST_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCTF_INFO_KIND (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCTF_INFO_VLEN (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ SHN_ABS ; 
 scalar_t__ SHN_UNDEF ; 
#define  STT_FUNC 129 
#define  STT_OBJECT 128 
 char* _CTF_NULLSTR ; 
 int /*<<< orphan*/  ctf_dprintf (char*,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 TYPE_4__* sym_to_gelf (int /*<<< orphan*/ *,TYPE_4__*) ; 

__attribute__((used)) static int
init_symtab(ctf_file_t *fp, const ctf_header_t *hp,
    const ctf_sect_t *sp, const ctf_sect_t *strp)
{
	const uchar_t *symp = sp->cts_data;
	uint_t *xp = fp->ctf_sxlate;
	uint_t *xend = xp + fp->ctf_nsyms;

	uint_t objtoff = hp->cth_objtoff;
	uint_t funcoff = hp->cth_funcoff;

	ushort_t info, vlen;
	Elf64_Sym sym, *gsp;
	const char *name;

	/*
	 * The CTF data object and function type sections are ordered to match
	 * the relative order of the respective symbol types in the symtab.
	 * If no type information is available for a symbol table entry, a
	 * pad is inserted in the CTF section.  As a further optimization,
	 * anonymous or undefined symbols are omitted from the CTF data.
	 */
	for (; xp < xend; xp++, symp += sp->cts_entsize) {
		if (sp->cts_entsize == sizeof (Elf32_Sym))
			gsp = sym_to_gelf((Elf32_Sym *)(uintptr_t)symp, &sym);
		else
			gsp = (Elf64_Sym *)(uintptr_t)symp;

		if (gsp->st_name < strp->cts_size)
			name = (const char *)strp->cts_data + gsp->st_name;
		else
			name = _CTF_NULLSTR;

		if (gsp->st_name == 0 || gsp->st_shndx == SHN_UNDEF ||
		    strcmp(name, "_START_") == 0 ||
		    strcmp(name, "_END_") == 0) {
			*xp = -1u;
			continue;
		}

		switch (ELF64_ST_TYPE(gsp->st_info)) {
		case STT_OBJECT:
			if (objtoff >= hp->cth_funcoff ||
			    (gsp->st_shndx == SHN_ABS && gsp->st_value == 0)) {
				*xp = -1u;
				break;
			}

			*xp = objtoff;
			objtoff += sizeof (ushort_t);
			break;

		case STT_FUNC:
			if (funcoff >= hp->cth_typeoff) {
				*xp = -1u;
				break;
			}

			*xp = funcoff;

			info = *(ushort_t *)((uintptr_t)fp->ctf_buf + funcoff);
			vlen = LCTF_INFO_VLEN(fp, info);

			/*
			 * If we encounter a zero pad at the end, just skip it.
			 * Otherwise skip over the function and its return type
			 * (+2) and the argument list (vlen).
			 */
			if (LCTF_INFO_KIND(fp, info) == CTF_K_UNKNOWN &&
			    vlen == 0)
				funcoff += sizeof (ushort_t); /* skip pad */
			else
				funcoff += sizeof (ushort_t) * (vlen + 2);
			break;

		default:
			*xp = -1u;
			break;
		}
	}

	ctf_dprintf("loaded %lu symtab entries\n", fp->ctf_nsyms);
	return (0);
}