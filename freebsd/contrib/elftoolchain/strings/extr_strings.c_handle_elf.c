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
struct stat {int /*<<< orphan*/  st_size; } ;
struct TYPE_6__ {scalar_t__ e_shnum; scalar_t__ e_type; } ;
struct TYPE_5__ {scalar_t__ sh_type; int sh_flags; int /*<<< orphan*/  sh_size; int /*<<< orphan*/  sh_offset; } ;
typedef  TYPE_1__ GElf_Shdr ;
typedef  TYPE_2__ GElf_Ehdr ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_C_READ ; 
 scalar_t__ ELF_K_ELF ; 
 scalar_t__ ET_CORE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int SHF_ALLOC ; 
 scalar_t__ SHT_NOBITS ; 
 int /*<<< orphan*/ * elf_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ *) ; 
 scalar_t__ elf_kind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * elf_nextscn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ entire_file ; 
 int fileno (int /*<<< orphan*/ *) ; 
 int find_strings (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/ * gelf_getehdr (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * gelf_getshdr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int handle_binary (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

int
handle_elf(const char *name, FILE *pfile)
{
	struct stat buf;
	GElf_Ehdr elfhdr;
	GElf_Shdr shdr;
	Elf *elf;
	Elf_Scn *scn;
	int rc, fd;

	rc = 0;
	fd = fileno(pfile);
	if (fstat(fd, &buf) < 0)
		return (1);

	/* If entire file is chosen, treat it as a binary file */
	if (entire_file)
		return (handle_binary(name, pfile, buf.st_size));

	(void)lseek(fd, 0, SEEK_SET);
	elf = elf_begin(fd, ELF_C_READ, NULL);
	if (elf_kind(elf) != ELF_K_ELF) {
		(void)elf_end(elf);
		return (handle_binary(name, pfile, buf.st_size));
	}

	if (gelf_getehdr(elf, &elfhdr) == NULL) {
		(void)elf_end(elf);
		warnx("%s: ELF file could not be processed", name);
		return (1);
	}

	if (elfhdr.e_shnum == 0 && elfhdr.e_type == ET_CORE) {
		(void)elf_end(elf);
		return (handle_binary(name, pfile, buf.st_size));
	} else {
		scn = NULL;
		while ((scn = elf_nextscn(elf, scn)) != NULL) {
			if (gelf_getshdr(scn, &shdr) == NULL)
				continue;
			if (shdr.sh_type != SHT_NOBITS &&
			    (shdr.sh_flags & SHF_ALLOC) != 0) {
				rc = find_strings(name, pfile, shdr.sh_offset,
				    shdr.sh_size);
			}
		}
	}
	(void)elf_end(elf);
	return (rc);
}