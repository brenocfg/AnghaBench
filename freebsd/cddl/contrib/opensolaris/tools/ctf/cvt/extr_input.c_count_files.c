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
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_C_READ ; 
#define  ELF_K_AR 129 
#define  ELF_K_ELF 128 
 int /*<<< orphan*/  EV_CURRENT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int count_archive (int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  debug (int,char*,int,int) ; 
 int /*<<< orphan*/ * elf_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_kind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_version (int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*,char*,...) ; 

int
count_files(char **files, int n)
{
	int nfiles = 0, err = 0;
	Elf *elf;
	int fd, rc, i;

	(void) elf_version(EV_CURRENT);

	for (i = 0; i < n; i++) {
		char *file = files[i];

		if ((fd = open(file, O_RDONLY)) < 0) {
			warning("Can't read input file %s", file);
			err++;
			continue;
		}

		if ((elf = elf_begin(fd, ELF_C_READ, NULL)) == NULL) {
			warning("Can't open input file %s: %s\n", file,
			    elf_errmsg(-1));
			err++;
			(void) close(fd);
			continue;
		}

		switch (elf_kind(elf)) {
		case ELF_K_AR:
			if ((rc = count_archive(fd, elf, file)) < 0)
				err++;
			else
				nfiles += rc;
			break;
		case ELF_K_ELF:
			nfiles++;
			break;
		default:
			warning("Input file %s is corrupt\n", file);
			err++;
		}

		(void) elf_end(elf);
		(void) close(fd);
	}

	if (err > 0)
		return (-1);

	debug(2, "Found %d files in %d input files\n", nfiles, n);

	return (nfiles);
}