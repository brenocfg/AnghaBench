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
struct TYPE_9__ {scalar_t__ sz; int /*<<< orphan*/  buf; } ;
struct TYPE_8__ {int sz; int /*<<< orphan*/  buf; } ;
struct symbuf {int nls; int ngs; TYPE_2__ g; TYPE_1__ l; int /*<<< orphan*/  g64; int /*<<< orphan*/  g32; int /*<<< orphan*/  l64; int /*<<< orphan*/  l32; } ;
struct strbuf {int nls; int ngs; TYPE_2__ g; TYPE_1__ l; int /*<<< orphan*/  g64; int /*<<< orphan*/  g32; int /*<<< orphan*/  l64; int /*<<< orphan*/  l32; } ;
struct section {int /*<<< orphan*/  os; int /*<<< orphan*/  sz; struct symbuf* buf; } ;
struct elfcopy {scalar_t__ oec; int /*<<< orphan*/  eout; struct section* strtab; struct section* symtab; } ;
struct TYPE_11__ {int d_align; int d_off; int d_size; void* d_version; void* d_type; int /*<<< orphan*/  d_buf; } ;
struct TYPE_10__ {int sh_addralign; int sh_info; scalar_t__ sh_link; scalar_t__ sh_entsize; scalar_t__ sh_flags; int /*<<< orphan*/  sh_type; int /*<<< orphan*/  sh_size; scalar_t__ sh_addr; } ;
typedef  TYPE_3__ GElf_Shdr ;
typedef  TYPE_4__ Elf_Data ;
typedef  int /*<<< orphan*/  Elf64_Sym ;
typedef  int /*<<< orphan*/  Elf32_Sym ;

/* Variables and functions */
 scalar_t__ ELFCLASS32 ; 
 void* ELF_T_BYTE ; 
 void* ELF_T_SYM ; 
 void* EV_CURRENT ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  SHT_STRTAB ; 
 int /*<<< orphan*/  SHT_SYMTAB ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 TYPE_4__* elf_newdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ gelf_fsize (int /*<<< orphan*/ ,void*,int,void*) ; 
 int /*<<< orphan*/ * gelf_getshdr (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  gelf_update_shdr (int /*<<< orphan*/ ,TYPE_3__*) ; 

void
create_symtab_data(struct elfcopy *ecp)
{
	struct section	*sy, *st;
	struct symbuf	*sy_buf;
	struct strbuf	*st_buf;
	Elf_Data	*gsydata, *lsydata, *gstdata, *lstdata;
	GElf_Shdr	 shy, sht;

	sy = ecp->symtab;
	st = ecp->strtab;

	if (gelf_getshdr(sy->os, &shy) == NULL)
		errx(EXIT_FAILURE, "gelf_getshdr() failed: %s",
		    elf_errmsg(-1));
	if (gelf_getshdr(st->os, &sht) == NULL)
		errx(EXIT_FAILURE, "gelf_getshdr() failed: %s",
		    elf_errmsg(-1));

	/*
	 * Create two Elf_Data for .symtab section of output object, one
	 * for local symbols and another for global symbols. Note that
	 * local symbols appear first in the .symtab.
	 */
	sy_buf = sy->buf;
	if (sy_buf->nls > 0) {
		if ((lsydata = elf_newdata(sy->os)) == NULL)
			errx(EXIT_FAILURE, "elf_newdata() failed: %s.",
			     elf_errmsg(-1));
		if (ecp->oec == ELFCLASS32) {
			lsydata->d_align	= 4;
			lsydata->d_off		= 0;
			lsydata->d_buf		= sy_buf->l32;
			lsydata->d_size		= sy_buf->nls *
				sizeof(Elf32_Sym);
			lsydata->d_type		= ELF_T_SYM;
			lsydata->d_version	= EV_CURRENT;
		} else {
			lsydata->d_align	= 8;
			lsydata->d_off		= 0;
			lsydata->d_buf		= sy_buf->l64;
			lsydata->d_size		= sy_buf->nls *
				sizeof(Elf64_Sym);
			lsydata->d_type		= ELF_T_SYM;
			lsydata->d_version	= EV_CURRENT;
		}
	}
	if (sy_buf->ngs > 0) {
		if ((gsydata = elf_newdata(sy->os)) == NULL)
			errx(EXIT_FAILURE, "elf_newdata() failed: %s.",
			     elf_errmsg(-1));
		if (ecp->oec == ELFCLASS32) {
			gsydata->d_align	= 4;
			gsydata->d_off		= sy_buf->nls *
				sizeof(Elf32_Sym);
			gsydata->d_buf		= sy_buf->g32;
			gsydata->d_size		= sy_buf->ngs *
				sizeof(Elf32_Sym);
			gsydata->d_type		= ELF_T_SYM;
			gsydata->d_version	= EV_CURRENT;
		} else {
			gsydata->d_align	= 8;
			gsydata->d_off		= sy_buf->nls *
				sizeof(Elf64_Sym);
			gsydata->d_buf		= sy_buf->g64;
			gsydata->d_size		= sy_buf->ngs *
				sizeof(Elf64_Sym);
			gsydata->d_type		= ELF_T_SYM;
			gsydata->d_version	= EV_CURRENT;
		}
	}

	/*
	 * Create two Elf_Data for .strtab, one for local symbol name
	 * and another for globals. Same as .symtab, local symbol names
	 * appear first.
	 */
	st_buf = st->buf;
	if ((lstdata = elf_newdata(st->os)) == NULL)
		errx(EXIT_FAILURE, "elf_newdata() failed: %s.",
		    elf_errmsg(-1));
	lstdata->d_align	= 1;
	lstdata->d_off		= 0;
	lstdata->d_buf		= st_buf->l.buf;
	lstdata->d_size		= st_buf->l.sz;
	lstdata->d_type		= ELF_T_BYTE;
	lstdata->d_version	= EV_CURRENT;

	if (st_buf->g.sz > 0) {
		if ((gstdata = elf_newdata(st->os)) == NULL)
			errx(EXIT_FAILURE, "elf_newdata() failed: %s.",
			    elf_errmsg(-1));
		gstdata->d_align	= 1;
		gstdata->d_off		= lstdata->d_size;
		gstdata->d_buf		= st_buf->g.buf;
		gstdata->d_size		= st_buf->g.sz;
		gstdata->d_type		= ELF_T_BYTE;
		gstdata->d_version	= EV_CURRENT;
	}

	shy.sh_addr		= 0;
	shy.sh_addralign	= (ecp->oec == ELFCLASS32 ? 4 : 8);
	shy.sh_size		= sy->sz;
	shy.sh_type		= SHT_SYMTAB;
	shy.sh_flags		= 0;
	shy.sh_entsize		= gelf_fsize(ecp->eout, ELF_T_SYM, 1,
	    EV_CURRENT);
	/*
	 * According to SYSV abi, here sh_info is one greater than
	 * the symbol table index of the last local symbol(binding
	 * STB_LOCAL).
	 */
	shy.sh_info		= sy_buf->nls;

	sht.sh_addr		= 0;
	sht.sh_addralign	= 1;
	sht.sh_size		= st->sz;
	sht.sh_type		= SHT_STRTAB;
	sht.sh_flags		= 0;
	sht.sh_entsize		= 0;
	sht.sh_info		= 0;
	sht.sh_link		= 0;

	if (!gelf_update_shdr(sy->os, &shy))
		errx(EXIT_FAILURE, "gelf_update_shdr() failed: %s",
		    elf_errmsg(-1));
	if (!gelf_update_shdr(st->os, &sht))
		errx(EXIT_FAILURE, "gelf_update_shdr() failed: %s",
		    elf_errmsg(-1));
}