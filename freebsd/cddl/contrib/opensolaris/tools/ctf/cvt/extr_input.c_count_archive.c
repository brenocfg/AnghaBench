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
struct TYPE_3__ {char* ar_name; } ;
typedef  int /*<<< orphan*/  Elf_Cmd ;
typedef  TYPE_1__ Elf_Arhdr ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_C_READ ; 
 int /*<<< orphan*/ * elf_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ *) ; 
 TYPE_1__* elf_getarhdr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warning (char*,char*) ; 

__attribute__((used)) static int
count_archive(int fd, Elf *elf, char *file)
{
	Elf *melf;
	Elf_Cmd cmd = ELF_C_READ;
	Elf_Arhdr *arh;
	int nfiles = 0, err = 0;

	while ((melf = elf_begin(fd, cmd, elf)) != NULL) {
		if ((arh = elf_getarhdr(melf)) == NULL) {
			warning("Can't process input archive %s\n",
			    file);
			err++;
		}

		if (*arh->ar_name != '/')
			nfiles++;

		cmd = elf_next(melf);
		(void) elf_end(melf);
	}

	if (err > 0)
		return (-1);

	return (nfiles);
}