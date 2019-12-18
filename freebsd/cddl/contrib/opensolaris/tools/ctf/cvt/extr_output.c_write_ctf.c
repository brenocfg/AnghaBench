#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tdata_t ;
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_3__ {int* e_ident; } ;
typedef  TYPE_1__ GElf_Ehdr ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 int CTF_SWAP_BYTES ; 
 size_t EI_DATA ; 
 int ELFDATA2LSB ; 
 int ELFDATA2MSB ; 
 int /*<<< orphan*/  ELF_C_READ ; 
 int /*<<< orphan*/  ELF_C_WRITE ; 
 int /*<<< orphan*/  EV_CURRENT ; 
 int O_CREAT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/ * elf_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elfterminate (char const*,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ gelf_getehdr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  make_ctf_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,size_t*,int) ; 
 int open (char const*,int,...) ; 
 int /*<<< orphan*/  terminate (char*,char const*) ; 
 int /*<<< orphan*/  write_file (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,size_t,int) ; 

void
write_ctf(tdata_t *td, const char *curname, const char *newname, int flags)
{
	struct stat st;
	Elf *elf = NULL;
	Elf *telf = NULL;
	GElf_Ehdr ehdr;
	caddr_t data;
	size_t len;
	int fd = -1;
	int tfd = -1;
	int byteorder;

	(void) elf_version(EV_CURRENT);
	if ((fd = open(curname, O_RDONLY)) < 0 || fstat(fd, &st) < 0)
		terminate("%s: Cannot open for re-reading", curname);
	if ((elf = elf_begin(fd, ELF_C_READ, NULL)) == NULL)
		elfterminate(curname, "Cannot re-read");

	if ((tfd = open(newname, O_RDWR | O_CREAT | O_TRUNC, st.st_mode)) < 0)
		terminate("Cannot open temp file %s for writing", newname);
	if ((telf = elf_begin(tfd, ELF_C_WRITE, NULL)) == NULL)
		elfterminate(curname, "Cannot write");

	if (gelf_getehdr(elf, &ehdr)) {
#if BYTE_ORDER == _BIG_ENDIAN
		byteorder = ELFDATA2MSB;
#else
		byteorder = ELFDATA2LSB;
#endif
		/*
		 * If target and host has the same byte order
		 * clear byte swapping request
		 */
		if  (ehdr.e_ident[EI_DATA] == byteorder)
			flags &= ~CTF_SWAP_BYTES;
	}
	else 
		elfterminate(curname, "Failed to get EHDR");

	data = make_ctf_data(td, elf, curname, &len, flags);
	write_file(elf, curname, telf, newname, data, len, flags);
	free(data);

	elf_end(telf);
	elf_end(elf);
	(void) close(fd);
	(void) close(tfd);
}