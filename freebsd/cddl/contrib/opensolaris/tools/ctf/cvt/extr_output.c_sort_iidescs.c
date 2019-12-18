#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tdata_t ;
struct TYPE_24__ {int /*<<< orphan*/  ii_flags; } ;
typedef  TYPE_1__ iidesc_t ;
struct TYPE_25__ {int iim_fuzzy; char* iim_file; char* iim_name; void* iim_bind; } ;
typedef  TYPE_2__ iidesc_match_t ;
struct TYPE_26__ {int iib_nobjts; int iib_nfuncs; int /*<<< orphan*/  iib_maxtypeid; TYPE_1__** iib_funcs; TYPE_1__** iib_objts; } ;
typedef  TYPE_3__ iiburst_t ;
struct TYPE_29__ {scalar_t__ d_buf; } ;
struct TYPE_28__ {int sh_size; int sh_entsize; int sh_link; } ;
struct TYPE_27__ {int st_name; int /*<<< orphan*/  st_info; } ;
typedef  TYPE_4__ GElf_Sym ;
typedef  TYPE_5__ GElf_Shdr ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  TYPE_6__ Elf_Data ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 void* GELF_ST_BIND (int /*<<< orphan*/ ) ; 
 int GELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IIDESC_F_USED ; 
#define  STT_FILE 130 
#define  STT_FUNC 129 
#define  STT_OBJECT 128 
 int /*<<< orphan*/  check_for_weak (TYPE_4__*,char*,TYPE_6__*,int,TYPE_6__*,TYPE_4__*,char**) ; 
 TYPE_1__* copy_from_strong (int /*<<< orphan*/ *,TYPE_4__*,TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  debug (int,char*,char*,char*) ; 
 TYPE_6__* elf_getdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * elf_getscn (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  elfterminate (char const*,char*,int) ; 
 TYPE_1__* find_iidesc (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int findelfsecidx (int /*<<< orphan*/ *,char const*,char*) ; 
 int /*<<< orphan*/  gelf_getshdr (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/ * gelf_getsym (TYPE_6__*,int,TYPE_4__*) ; 
 scalar_t__ ignore_symbol (TYPE_4__*,char*) ; 
 TYPE_3__* iiburst_new (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  iiburst_types (TYPE_3__*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  tdata_label_newmax (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  terminate (char*,char const*) ; 

__attribute__((used)) static iiburst_t *
sort_iidescs(Elf *elf, const char *file, tdata_t *td, int fuzzymatch,
    int dynsym)
{
	iiburst_t *iiburst;
	Elf_Scn *scn;
	GElf_Shdr shdr;
	Elf_Data *data, *strdata;
	int i, stidx;
	int nent;
	iidesc_match_t match;

	match.iim_fuzzy = fuzzymatch;
	match.iim_file = NULL;

	if ((stidx = findelfsecidx(elf, file,
	    dynsym ? ".dynsym" : ".symtab")) < 0)
		terminate("%s: Can't open symbol table\n", file);
	scn = elf_getscn(elf, stidx);
	data = elf_getdata(scn, NULL);
	gelf_getshdr(scn, &shdr);
	nent = shdr.sh_size / shdr.sh_entsize;

	scn = elf_getscn(elf, shdr.sh_link);
	strdata = elf_getdata(scn, NULL);

	iiburst = iiburst_new(td, nent);

	for (i = 0; i < nent; i++) {
		GElf_Sym sym;
		char *bname;
		iidesc_t **tolist;
		GElf_Sym ssym;
		iidesc_match_t smatch;
		int *curr;
		iidesc_t *iidesc;

		if (gelf_getsym(data, i, &sym) == NULL)
			elfterminate(file, "Couldn't read symbol %d", i);

		match.iim_name = (char *)strdata->d_buf + sym.st_name;
		match.iim_bind = GELF_ST_BIND(sym.st_info);

		switch (GELF_ST_TYPE(sym.st_info)) {
		case STT_FILE:
			bname = strrchr(match.iim_name, '/');
			match.iim_file = bname == NULL ? match.iim_name : bname + 1;
			continue;
		case STT_OBJECT:
			tolist = iiburst->iib_objts;
			curr = &iiburst->iib_nobjts;
			break;
		case STT_FUNC:
			tolist = iiburst->iib_funcs;
			curr = &iiburst->iib_nfuncs;
			break;
		default:
			continue;
		}

		if (ignore_symbol(&sym, match.iim_name))
			continue;

		iidesc = find_iidesc(td, &match);

		if (iidesc != NULL) {
			tolist[*curr] = iidesc;
			iidesc->ii_flags |= IIDESC_F_USED;
			(*curr)++;
			continue;
		}

		if (!check_for_weak(&sym, match.iim_file, data, nent, strdata,
		    &ssym, &smatch.iim_file)) {
			(*curr)++;
			continue;
		}

		smatch.iim_fuzzy = fuzzymatch;
		smatch.iim_name = (char *)strdata->d_buf + ssym.st_name;
		smatch.iim_bind = GELF_ST_BIND(ssym.st_info);

		debug(3, "Weak symbol %s resolved to %s\n", match.iim_name,
		    smatch.iim_name);

		iidesc = find_iidesc(td, &smatch);

		if (iidesc != NULL) {
			tolist[*curr] = copy_from_strong(td, &sym,
			    iidesc, match.iim_name, match.iim_file);
			tolist[*curr]->ii_flags |= IIDESC_F_USED;
		}

		(*curr)++;
	}

	/*
	 * Stabs are generated for every function declared in a given C source
	 * file.  When converting an object file, we may encounter a stab that
	 * has no symbol table entry because the optimizer has decided to omit
	 * that item (for example, an unreferenced static function).  We may
	 * see iidescs that do not have an associated symtab entry, and so
	 * we do not write records for those functions into the CTF data.
	 * All others get marked as a root by this function.
	 */
	iiburst_types(iiburst);

	/*
	 * By not adding some of the functions and/or objects, we may have
	 * caused some types that were referenced solely by those
	 * functions/objects to be suppressed.  This could cause a label,
	 * generated prior to the evisceration, to be incorrect.  Find the
	 * highest type index, and change the label indicies to be no higher
	 * than this value.
	 */
	tdata_label_newmax(td, iiburst->iib_maxtypeid);

	return (iiburst);
}