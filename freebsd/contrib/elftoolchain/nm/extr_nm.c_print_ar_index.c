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
typedef  scalar_t__ off_t ;
struct TYPE_6__ {char* ar_name; char* ar_rawname; } ;
struct TYPE_5__ {scalar_t__ as_off; char* as_name; } ;
typedef  int /*<<< orphan*/  Elf_Cmd ;
typedef  TYPE_1__ Elf_Arsym ;
typedef  TYPE_2__ Elf_Arhdr ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_C_READ ; 
 int /*<<< orphan*/ * elf_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ *) ; 
 TYPE_2__* elf_getarhdr (int /*<<< orphan*/ *) ; 
 TYPE_1__* elf_getarsym (int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ elf_rand (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_ar_index(int fd, Elf *arf)
{
	Elf *elf;
	Elf_Arhdr *arhdr;
	Elf_Arsym *arsym;
	Elf_Cmd cmd;
	off_t start;
	size_t arsym_size;

	if (arf == NULL)
		return;

	if ((arsym = elf_getarsym(arf, &arsym_size)) == NULL)
		return;

	printf("\nArchive index:\n");

	start = arsym->as_off;
	cmd = ELF_C_READ;
	while (arsym_size > 1) {
		if (elf_rand(arf, arsym->as_off) == arsym->as_off &&
		    (elf = elf_begin(fd, cmd, arf)) != NULL) {
			if ((arhdr = elf_getarhdr(elf)) != NULL)
				printf("%s in %s\n", arsym->as_name,
				    arhdr->ar_name != NULL ?
				    arhdr->ar_name : arhdr->ar_rawname);
			elf_end(elf);
		}
		++arsym;
		--arsym_size;
	}

	elf_rand(arf, start);
}