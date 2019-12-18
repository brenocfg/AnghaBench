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
struct elfdump {char* filename; char* archive; int flags; int /*<<< orphan*/ * elf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_C_READ ; 
#define  ELF_K_AR 130 
#define  ELF_K_ELF 129 
#define  ELF_K_NONE 128 
 int /*<<< orphan*/  O_RDONLY ; 
 int PRINT_FILENAME ; 
 scalar_t__ ac_detect_ar (int) ; 
 int /*<<< orphan*/  ac_print_ar (struct elfdump*,int) ; 
 int /*<<< orphan*/ * elf_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_kind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_print_ar (struct elfdump*,int) ; 
 int /*<<< orphan*/  elf_print_elf (struct elfdump*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static void
elf_print_object(struct elfdump *ed)
{
	int fd;

	if ((fd = open(ed->filename, O_RDONLY)) == -1) {
		warn("open %s failed", ed->filename);
		return;
	}

#ifdef	USE_LIBARCHIVE_AR
	if (ac_detect_ar(fd)) {
		ed->archive = ed->filename;
		ac_print_ar(ed, fd);
		return;
	}
#endif	/* USE_LIBARCHIVE_AR */

	if ((ed->elf = elf_begin(fd, ELF_C_READ, NULL)) == NULL) {
		warnx("elf_begin() failed: %s", elf_errmsg(-1));
		return;
	}

	switch (elf_kind(ed->elf)) {
	case ELF_K_NONE:
		warnx("Not an ELF file.");
		return;
	case ELF_K_ELF:
		if (ed->flags & PRINT_FILENAME)
			printf("\n%s:\n", ed->filename);
		elf_print_elf(ed);
		break;
	case ELF_K_AR:
#ifndef	USE_LIBARCHIVE_AR
		ed->archive = ed->filename;
		elf_print_ar(ed, fd);
#endif
		break;
	default:
		warnx("Internal: libelf returned unknown elf kind.");
		return;
	}

	elf_end(ed->elf);
}