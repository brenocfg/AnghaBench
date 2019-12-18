#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_t ;
typedef  int /*<<< orphan*/  syment_t ;
struct TYPE_10__ {scalar_t__ d_buf; } ;
struct TYPE_9__ {scalar_t__ addr; char* name; int size; } ;
struct TYPE_8__ {scalar_t__ sh_type; int sh_size; int sh_entsize; int sh_link; } ;
struct TYPE_7__ {scalar_t__ st_size; int st_name; scalar_t__ st_value; int /*<<< orphan*/  st_info; } ;
typedef  TYPE_1__ Sym ;
typedef  TYPE_2__ Shdr ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 scalar_t__ ELF32_ST_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ELF_C_READ ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  EV_CURRENT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ SHT_SYMTAB ; 
 int STT_FUNC ; 
 uintptr_t ULONG_MAX ; 
 int /*<<< orphan*/  add_symbol (char*,uintptr_t,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/ * elf_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_6__* elf_getdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* elf_getshdr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * elf_nextscn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_version (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fake_up_certain_popular_kernel_symbols () ; 
 int /*<<< orphan*/  kldload (char*) ; 
 char* maxsymname ; 
 int modfind (char*) ; 
 int nsyms ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort (TYPE_3__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,uintptr_t) ; 
 TYPE_3__* symbol_table ; 
 int /*<<< orphan*/  symcmp ; 

int
symtab_init(void)
{
	Elf		*elf;
	Elf_Scn		*scn = NULL;
	Sym		*symtab, *symp, *lastsym;
	char		*strtab;
	uint_t		cnt;
	int		fd;
	int		i;
	int		strindex = -1;

#ifndef illumos
	if ((fd = open("/dev/ksyms", O_RDONLY)) == -1) {
		if (errno == ENOENT && modfind("ksyms") == -1) {
			kldload("ksyms");
			fd = open("/dev/ksyms", O_RDONLY);
		}
		if (fd == -1)
			return (-1);
	}
#else
	if ((fd = open("/dev/ksyms", O_RDONLY)) == -1)
		return (-1);
#endif

	(void) elf_version(EV_CURRENT);

	elf = elf_begin(fd, ELF_C_READ, NULL);

	for (cnt = 1; (scn = elf_nextscn(elf, scn)) != NULL; cnt++) {
		Shdr *shdr = elf_getshdr(scn);
		if (shdr->sh_type == SHT_SYMTAB) {
			symtab = (Sym *)elf_getdata(scn, NULL)->d_buf;
			nsyms = shdr->sh_size / shdr->sh_entsize;
			strindex = shdr->sh_link;
		}
	}

	for (cnt = 1; (scn = elf_nextscn(elf, scn)) != NULL; cnt++) {
		if (cnt == strindex)
			strtab = (char *)elf_getdata(scn, NULL)->d_buf;
	}

	lastsym = symtab + nsyms;
	nsyms = 0;
	for (symp = symtab; symp < lastsym; symp++)
		if ((uint_t)ELF32_ST_TYPE(symp->st_info) <= STT_FUNC &&
		    symp->st_size != 0)
			add_symbol(symp->st_name + strtab,
			    (uintptr_t)symp->st_value, (size_t)symp->st_size);

	fake_up_certain_popular_kernel_symbols();
	(void) sprintf(maxsymname, "0x%lx", ULONG_MAX);
	add_symbol(maxsymname, ULONG_MAX, 1);

	qsort(symbol_table, nsyms, sizeof (syment_t), symcmp);

	/*
	 * Destroy all duplicate symbols, then sort it again.
	 */
	for (i = 0; i < nsyms - 1; i++)
		if (symbol_table[i].addr == symbol_table[i + 1].addr)
			symbol_table[i].addr = 0;

	qsort(symbol_table, nsyms, sizeof (syment_t), symcmp);

	while (symbol_table[1].addr == 0) {
		symbol_table++;
		nsyms--;
	}
	symbol_table[0].name = "(usermode)";
	symbol_table[0].addr = 0;
	symbol_table[0].size = 1;

	close(fd);
	return (0);
}