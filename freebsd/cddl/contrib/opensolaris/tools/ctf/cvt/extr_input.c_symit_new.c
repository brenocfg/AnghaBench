#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int sh_link; int sh_size; int sh_entsize; } ;
struct TYPE_5__ {int si_nument; TYPE_4__ si_shdr; int /*<<< orphan*/ * si_strd; int /*<<< orphan*/ * si_symd; } ;
typedef  TYPE_1__ symit_data_t ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 void* elf_getdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * elf_getscn (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  elfterminate (char const*,char*) ; 
 int findelfsecidx (int /*<<< orphan*/ *,char const*,char*) ; 
 int /*<<< orphan*/ * gelf_getshdr (int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_1__* xcalloc (int) ; 

symit_data_t *
symit_new(Elf *elf, const char *file)
{
	symit_data_t *si;
	Elf_Scn *scn;
	int symtabidx;

	if ((symtabidx = findelfsecidx(elf, file, ".symtab")) < 0)
		return (NULL);

	si = xcalloc(sizeof (symit_data_t));

	if ((scn = elf_getscn(elf, symtabidx)) == NULL ||
	    gelf_getshdr(scn, &si->si_shdr) == NULL ||
	    (si->si_symd = elf_getdata(scn, NULL)) == NULL)
		elfterminate(file, "Cannot read .symtab");

	if ((scn = elf_getscn(elf, si->si_shdr.sh_link)) == NULL ||
	    (si->si_strd = elf_getdata(scn, NULL)) == NULL)
		elfterminate(file, "Cannot read strings for .symtab");

	si->si_nument = si->si_shdr.sh_size / si->si_shdr.sh_entsize;

	return (si);
}