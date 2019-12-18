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
struct TYPE_6__ {int /*<<< orphan*/  e_shstrndx; } ;
struct TYPE_5__ {scalar_t__ sh_name; } ;
typedef  TYPE_1__ GElf_Shdr ;
typedef  TYPE_2__ GElf_Ehdr ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 int elf_ndxscn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * elf_nextscn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* elf_strptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  elfterminate (char const*,char*,...) ; 
 int /*<<< orphan*/ * gelf_getehdr (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * gelf_getshdr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ strcmp (char*,char const*) ; 

int
findelfsecidx(Elf *elf, const char *file, const char *tofind)
{
	Elf_Scn *scn = NULL;
	GElf_Ehdr ehdr;
	GElf_Shdr shdr;

	if (gelf_getehdr(elf, &ehdr) == NULL)
		elfterminate(file, "Couldn't read ehdr");

	while ((scn = elf_nextscn(elf, scn)) != NULL) {
		char *name;

		if (gelf_getshdr(scn, &shdr) == NULL) {
			elfterminate(file,
			    "Couldn't read header for section %d",
			    elf_ndxscn(scn));
		}

		if ((name = elf_strptr(elf, ehdr.e_shstrndx,
		    (size_t)shdr.sh_name)) == NULL) {
			elfterminate(file,
			    "Couldn't get name for section %d",
			    elf_ndxscn(scn));
		}

		if (strcmp(name, tofind) == 0)
			return (elf_ndxscn(scn));
	}

	return (-1);
}