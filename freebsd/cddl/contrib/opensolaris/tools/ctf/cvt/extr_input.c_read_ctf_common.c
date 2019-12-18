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
typedef  int /*<<< orphan*/  read_cb_f ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_C_READ ; 
#define  ELF_K_AR 129 
#define  ELF_K_ELF 128 
 int /*<<< orphan*/  EV_CURRENT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  debug (int,char*,char*,char*) ; 
 int /*<<< orphan*/ * elf_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ *) ; 
 int elf_kind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elfterminate (char*,char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read_archive (int,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,void*,int) ; 
 int read_file (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  terminate (char*,char*,...) ; 

__attribute__((used)) static int
read_ctf_common(char *file, char *label, read_cb_f *func, void *arg,
    int require_ctf)
{
	Elf *elf;
	int found = 0;
	int fd;

	debug(3, "Reading %s (label %s)\n", file, (label ? label : "NONE"));

	(void) elf_version(EV_CURRENT);

	if ((fd = open(file, O_RDONLY)) < 0)
		terminate("%s: Cannot open for reading", file);
	if ((elf = elf_begin(fd, ELF_C_READ, NULL)) == NULL)
		elfterminate(file, "Cannot read");

	switch (elf_kind(elf)) {
	case ELF_K_AR:
		found = read_archive(fd, elf, file, label,
		    func, arg, require_ctf);
		break;

	case ELF_K_ELF:
		found = read_file(elf, file, label,
		    func, arg, require_ctf);
		break;

	default:
		terminate("%s: Unknown elf kind %d\n", file, elf_kind(elf));
	}

	(void) elf_end(elf);
	(void) close(fd);

	return (found);
}