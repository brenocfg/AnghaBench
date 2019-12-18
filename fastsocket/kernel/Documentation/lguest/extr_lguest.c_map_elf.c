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
typedef  int /*<<< orphan*/  phdr ;
struct TYPE_6__ {int e_phnum; scalar_t__ e_type; scalar_t__ e_machine; int e_phentsize; unsigned long e_entry; int /*<<< orphan*/  e_phoff; } ;
struct TYPE_5__ {scalar_t__ p_type; int /*<<< orphan*/  p_filesz; int /*<<< orphan*/  p_offset; scalar_t__ p_paddr; int /*<<< orphan*/  p_memsz; } ;
typedef  TYPE_1__ Elf32_Phdr ;
typedef  TYPE_2__ Elf32_Ehdr ;

/* Variables and functions */
 scalar_t__ EM_386 ; 
 scalar_t__ ET_EXEC ; 
 scalar_t__ PT_LOAD ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  from_guest_phys (scalar_t__) ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_at (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read (int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  verbose (char*,unsigned int,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static unsigned long map_elf(int elf_fd, const Elf32_Ehdr *ehdr)
{
	Elf32_Phdr phdr[ehdr->e_phnum];
	unsigned int i;

	/*
	 * Sanity checks on the main ELF header: an x86 executable with a
	 * reasonable number of correctly-sized program headers.
	 */
	if (ehdr->e_type != ET_EXEC
	    || ehdr->e_machine != EM_386
	    || ehdr->e_phentsize != sizeof(Elf32_Phdr)
	    || ehdr->e_phnum < 1 || ehdr->e_phnum > 65536U/sizeof(Elf32_Phdr))
		errx(1, "Malformed elf header");

	/*
	 * An ELF executable contains an ELF header and a number of "program"
	 * headers which indicate which parts ("segments") of the program to
	 * load where.
	 */

	/* We read in all the program headers at once: */
	if (lseek(elf_fd, ehdr->e_phoff, SEEK_SET) < 0)
		err(1, "Seeking to program headers");
	if (read(elf_fd, phdr, sizeof(phdr)) != sizeof(phdr))
		err(1, "Reading program headers");

	/*
	 * Try all the headers: there are usually only three.  A read-only one,
	 * a read-write one, and a "note" section which we don't load.
	 */
	for (i = 0; i < ehdr->e_phnum; i++) {
		/* If this isn't a loadable segment, we ignore it */
		if (phdr[i].p_type != PT_LOAD)
			continue;

		verbose("Section %i: size %i addr %p\n",
			i, phdr[i].p_memsz, (void *)phdr[i].p_paddr);

		/* We map this section of the file at its physical address. */
		map_at(elf_fd, from_guest_phys(phdr[i].p_paddr),
		       phdr[i].p_offset, phdr[i].p_filesz);
	}

	/* The entry point is given in the ELF header. */
	return ehdr->e_entry;
}