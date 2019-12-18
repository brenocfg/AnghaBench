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
struct TYPE_3__ {scalar_t__ e_cmd; int e_fd; scalar_t__ e_parent; } ;
typedef  scalar_t__ Elf_Cmd ;
typedef  TYPE_1__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE ; 
 int /*<<< orphan*/  ARGUMENT ; 
 scalar_t__ ELF_C_FDDONE ; 
 scalar_t__ ELF_C_FDREAD ; 
 scalar_t__ ELF_C_WRITE ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MODE ; 

int
elf_cntl(Elf *e, Elf_Cmd c)
{
	if (e == NULL ||
	    (c != ELF_C_FDDONE && c != ELF_C_FDREAD)) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (-1);
	}

	if (e->e_parent) {
		LIBELF_SET_ERROR(ARCHIVE, 0);
		return (-1);
	}

	if (c == ELF_C_FDREAD) {
		if (e->e_cmd == ELF_C_WRITE) {
			LIBELF_SET_ERROR(MODE, 0);
			return (-1);
		}
		else
			return (0);
	}

	e->e_fd = -1;
	return 0;
}