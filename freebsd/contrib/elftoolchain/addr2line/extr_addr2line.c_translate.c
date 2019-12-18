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
typedef  int /*<<< orphan*/  uintmax_t ;
struct Func {char* name; int /*<<< orphan*/  call_line; int /*<<< orphan*/  call_file; int /*<<< orphan*/ * inlined_caller; } ;
struct CU {int /*<<< orphan*/ * srcfiles; int /*<<< orphan*/  funclist; int /*<<< orphan*/  nsrcfiles; void* hipc; void* lopc; int /*<<< orphan*/  off; } ;
typedef  int /*<<< orphan*/  off ;
typedef  int /*<<< orphan*/  demangled ;
typedef  int /*<<< orphan*/  Elf ;
typedef  void* Dwarf_Unsigned ;
typedef  int Dwarf_Signed ;
typedef  int /*<<< orphan*/  Dwarf_Off ;
typedef  int /*<<< orphan*/  Dwarf_Line ;
typedef  scalar_t__ Dwarf_Half ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/ * Dwarf_Die ;
typedef  int /*<<< orphan*/  Dwarf_Debug ;
typedef  void* Dwarf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  DW_AT_high_pc ; 
 int /*<<< orphan*/  DW_AT_low_pc ; 
 int /*<<< orphan*/  DW_DLA_DIE ; 
 int DW_DLV_ERROR ; 
#define  DW_DLV_NO_ENTRY 129 
#define  DW_DLV_OK 128 
 scalar_t__ DW_TAG_compile_unit ; 
 int ELFCLASS32 ; 
 int ELFCLASS64 ; 
 int ELFCLASSNONE ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  HASH_ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct CU*) ; 
 int /*<<< orphan*/  HASH_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct CU*) ; 
 scalar_t__ STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 scalar_t__ base ; 
 char* basename (char*) ; 
 struct CU* calloc (int,int) ; 
 int /*<<< orphan*/  collect_func (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct CU*) ; 
 int /*<<< orphan*/  culist ; 
 scalar_t__ demangle ; 
 int dwarf_attrval_unsigned (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_dealloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dwarf_dieoffset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_errmsg (int /*<<< orphan*/ ) ; 
 scalar_t__ dwarf_lineaddr (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_lineno (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_linesrc (int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 
 int dwarf_next_cu_header (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dwarf_siblingof (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_srcfiles (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dwarf_srclines (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *) ; 
 int dwarf_tag (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int /*<<< orphan*/  elftc_demangle (char const*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ func ; 
 int gelf_getclass (int /*<<< orphan*/ *) ; 
 int handle_high_pc (int /*<<< orphan*/ *,void*,void**) ; 
 int /*<<< orphan*/  hh ; 
 scalar_t__ inlines ; 
 scalar_t__ pretty_print ; 
 scalar_t__ print_addr ; 
 int /*<<< orphan*/  print_inlines (struct CU*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 struct Func* search_func (struct CU*,void*) ; 
 scalar_t__ section_base ; 
 void* strtoull (char const*,int /*<<< orphan*/ *,int) ; 
 void* unknown ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static void
translate(Dwarf_Debug dbg, Elf *e, const char* addrstr)
{
	Dwarf_Die die, ret_die;
	Dwarf_Line *lbuf;
	Dwarf_Error de;
	Dwarf_Half tag;
	Dwarf_Unsigned lopc, hipc, addr, lineno, plineno;
	Dwarf_Signed lcount;
	Dwarf_Addr lineaddr, plineaddr;
	Dwarf_Off off;
	struct CU *cu;
	struct Func *f;
	const char *funcname;
	char *file, *file0, *pfile;
	char demangled[1024];
	int ec, i, ret;

	addr = strtoull(addrstr, NULL, 16);
	addr += section_base;
	lineno = 0;
	file = unknown;
	cu = NULL;
	die = NULL;

	while ((ret = dwarf_next_cu_header(dbg, NULL, NULL, NULL, NULL, NULL,
	    &de)) ==  DW_DLV_OK) {
		die = NULL;
		while (dwarf_siblingof(dbg, die, &ret_die, &de) == DW_DLV_OK) {
			if (die != NULL)
				dwarf_dealloc(dbg, die, DW_DLA_DIE);
			die = ret_die;
			if (dwarf_tag(die, &tag, &de) != DW_DLV_OK) {
				warnx("dwarf_tag failed: %s",
				    dwarf_errmsg(de));
				goto next_cu;
			}

			/* XXX: What about DW_TAG_partial_unit? */
			if (tag == DW_TAG_compile_unit)
				break;
		}
		if (ret_die == NULL) {
			warnx("could not find DW_TAG_compile_unit die");
			goto next_cu;
		}
		if (dwarf_attrval_unsigned(die, DW_AT_low_pc, &lopc, &de) ==
		    DW_DLV_OK) {
			if (dwarf_attrval_unsigned(die, DW_AT_high_pc, &hipc,
			   &de) == DW_DLV_OK) {
				/*
				 * Check if the address falls into the PC
				 * range of this CU.
				 */
				if (handle_high_pc(die, lopc, &hipc) !=
				    DW_DLV_OK)
					goto out;
			} else {
				/* Assume ~0ULL if DW_AT_high_pc not present */
				hipc = ~0ULL;
			}

			/*
			 * Record the CU in the hash table for faster lookup
			 * later.
			 */
			if (dwarf_dieoffset(die, &off, &de) != DW_DLV_OK) {
				warnx("dwarf_dieoffset failed: %s",
				    dwarf_errmsg(de));
				goto out;
			}
			HASH_FIND(hh, culist, &off, sizeof(off), cu);
			if (cu == NULL) {
				if ((cu = calloc(1, sizeof(*cu))) == NULL)
					err(EXIT_FAILURE, "calloc");
				cu->off = off;
				cu->lopc = lopc;
				cu->hipc = hipc;
				STAILQ_INIT(&cu->funclist);
				HASH_ADD(hh, culist, off, sizeof(off), cu);
			}

			if (addr >= lopc && addr < hipc)
				break;
		}

	next_cu:
		if (die != NULL) {
			dwarf_dealloc(dbg, die, DW_DLA_DIE);
			die = NULL;
		}
	}

	if (ret != DW_DLV_OK || die == NULL)
		goto out;

	switch (dwarf_srclines(die, &lbuf, &lcount, &de)) {
	case DW_DLV_OK:
		break;
	case DW_DLV_NO_ENTRY:
		/* If a CU lacks debug info, just skip it. */
		goto out;
	default:
		warnx("dwarf_srclines: %s", dwarf_errmsg(de));
		goto out;
	}

	plineaddr = ~0ULL;
	plineno = 0;
	pfile = unknown;
	for (i = 0; i < lcount; i++) {
		if (dwarf_lineaddr(lbuf[i], &lineaddr, &de)) {
			warnx("dwarf_lineaddr: %s", dwarf_errmsg(de));
			goto out;
		}
		if (dwarf_lineno(lbuf[i], &lineno, &de)) {
			warnx("dwarf_lineno: %s", dwarf_errmsg(de));
			goto out;
		}
		if (dwarf_linesrc(lbuf[i], &file0, &de)) {
			warnx("dwarf_linesrc: %s", dwarf_errmsg(de));
		} else
			file = file0;
		if (addr == lineaddr)
			goto out;
		else if (addr < lineaddr && addr > plineaddr) {
			lineno = plineno;
			file = pfile;
			goto out;
		}
		plineaddr = lineaddr;
		plineno = lineno;
		pfile = file;
	}

out:
	f = NULL;
	funcname = NULL;
	if (ret == DW_DLV_OK && (func || inlines) && cu != NULL) {
		if (cu->srcfiles == NULL)
			if (dwarf_srcfiles(die, &cu->srcfiles, &cu->nsrcfiles,
			    &de))
				warnx("dwarf_srcfiles: %s", dwarf_errmsg(de));
		if (STAILQ_EMPTY(&cu->funclist)) {
			collect_func(dbg, die, NULL, cu);
			die = NULL;
		}
		f = search_func(cu, addr);
		if (f != NULL)
			funcname = f->name;
	}

	if (print_addr) {
		if ((ec = gelf_getclass(e)) == ELFCLASSNONE) {
			warnx("gelf_getclass failed: %s", elf_errmsg(-1));
			ec = ELFCLASS64;
		}
		if (ec == ELFCLASS32) {
			if (pretty_print)
				printf("0x%08jx: ", (uintmax_t) addr);
			else
				printf("0x%08jx\n", (uintmax_t) addr);
		} else {
			if (pretty_print)
				printf("0x%016jx: ", (uintmax_t) addr);
			else
				printf("0x%016jx\n", (uintmax_t) addr);
		}
	}

	if (func) {
		if (funcname == NULL)
			funcname = unknown;
		if (demangle && !elftc_demangle(funcname, demangled,
		    sizeof(demangled), 0)) {
			if (pretty_print)
				printf("%s at ", demangled);
			else
				printf("%s\n", demangled);
		} else {
			if (pretty_print)
				printf("%s at ", funcname);
			else
				printf("%s\n", funcname);
		}
	}

	(void) printf("%s:%ju\n", base ? basename(file) : file,
	    (uintmax_t) lineno);

	if (ret == DW_DLV_OK && inlines && cu != NULL &&
	    cu->srcfiles != NULL && f != NULL && f->inlined_caller != NULL)
		print_inlines(cu, f->inlined_caller, f->call_file,
		    f->call_line);

	if (die != NULL)
		dwarf_dealloc(dbg, die, DW_DLA_DIE);

	/*
	 * Reset internal CU pointer, so we will start from the first CU
	 * next round.
	 */
	while (ret != DW_DLV_NO_ENTRY) {
		if (ret == DW_DLV_ERROR)
			errx(EXIT_FAILURE, "dwarf_next_cu_header: %s",
			    dwarf_errmsg(de));
		ret = dwarf_next_cu_header(dbg, NULL, NULL, NULL, NULL, NULL,
		    &de);
	}
}