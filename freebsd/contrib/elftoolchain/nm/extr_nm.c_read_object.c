#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ print_name; scalar_t__ elem_print_fn; int print_armap; int /*<<< orphan*/  fileargs; } ;
typedef  scalar_t__ Elf_Kind ;
typedef  int /*<<< orphan*/  Elf_Cmd ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_C_READ ; 
 scalar_t__ ELF_K_AR ; 
 scalar_t__ ELF_K_NONE ; 
 scalar_t__ PRINT_NAME_MULTI ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/ * elf_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ *) ; 
 char const* elf_errmsg (int) ; 
 int elf_errno () ; 
 scalar_t__ elf_kind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_next (int /*<<< orphan*/ *) ; 
 int fileargs_open (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__ nm_opts ; 
 int /*<<< orphan*/  print_ar_index (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int read_elf (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 scalar_t__ sym_elem_print_all ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
read_object(const char *filename)
{
	Elf *elf, *arf;
	Elf_Cmd elf_cmd;
	Elf_Kind kind;
	int fd, rtn, e_err;

	assert(filename != NULL && "filename is null");

	if ((fd = fileargs_open(nm_opts.fileargs, filename)) == -1) {
		warn("'%s'", filename);
		return (1);
	}

	elf_cmd = ELF_C_READ;
	if ((arf = elf_begin(fd, elf_cmd, (Elf *) NULL)) == NULL) {
		if ((e_err = elf_errno()) != 0)
			warnx("elf_begin error: %s", elf_errmsg(e_err));
		else
			warnx("elf_begin error");
		close(fd);
		return (1);
	}

	assert(arf != NULL && "arf is null.");

	rtn = 0;
	if ((kind = elf_kind(arf)) == ELF_K_NONE) {
		warnx("%s: File format not recognized", filename);
		elf_end(arf);
		close(fd);
		return (1);
	}
	if (kind == ELF_K_AR) {
		if (nm_opts.print_name == PRINT_NAME_MULTI &&
		    nm_opts.elem_print_fn == sym_elem_print_all)
			printf("\n%s:\n", filename);
		if (nm_opts.print_armap == true)
			print_ar_index(fd, arf);
	}

	while ((elf = elf_begin(fd, elf_cmd, arf)) != NULL) {
		rtn |= read_elf(elf, filename, kind);

		/*
		 * If file is not archive, elf_next return ELF_C_NULL and
		 * stop the loop.
		 */
		elf_cmd = elf_next(elf);
		elf_end(elf);
	}

	elf_end(arf);
	close(fd);

	return (rtn);
}