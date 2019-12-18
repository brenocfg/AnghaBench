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
struct readelf {int flags; char* filename; int /*<<< orphan*/ * elf; } ;

/* Variables and functions */
 int DISPLAY_FILENAME ; 
 int /*<<< orphan*/  ELF_C_READ ; 
#define  ELF_K_AR 130 
#define  ELF_K_ELF 129 
#define  ELF_K_NONE 128 
 int /*<<< orphan*/  dump_ar (struct readelf*,int) ; 
 int /*<<< orphan*/  dump_elf (struct readelf*) ; 
 int /*<<< orphan*/ * elf_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_kind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static void
dump_object(struct readelf *re, int fd)
{
	if ((re->flags & DISPLAY_FILENAME) != 0)
		printf("\nFile: %s\n", re->filename);

	if ((re->elf = elf_begin(fd, ELF_C_READ, NULL)) == NULL) {
		warnx("elf_begin() failed: %s", elf_errmsg(-1));
		return;
	}

	switch (elf_kind(re->elf)) {
	case ELF_K_NONE:
		warnx("Not an ELF file.");
		return;
	case ELF_K_ELF:
		dump_elf(re);
		break;
	case ELF_K_AR:
		dump_ar(re, fd);
		break;
	default:
		warnx("Internal: libelf returned unknown elf kind.");
		return;
	}

	elf_end(re->elf);
}