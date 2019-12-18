#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int e_fd; int e_cmd; scalar_t__ e_kind; int /*<<< orphan*/  e_activations; } ;
typedef  int Elf_Cmd ;
typedef  TYPE_1__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
#define  ELF_C_NULL 131 
#define  ELF_C_RDWR 130 
#define  ELF_C_READ 129 
#define  ELF_C_WRITE 128 
 scalar_t__ ELF_K_AR ; 
 scalar_t__ EV_NONE ; 
 scalar_t__ LIBELF_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEQUENCE ; 
 TYPE_1__* _libelf_ar_open_member (int,int,TYPE_1__*) ; 
 TYPE_1__* _libelf_open_object (int,int,int) ; 
 int /*<<< orphan*/  version ; 

Elf *
elf_begin(int fd, Elf_Cmd c, Elf *a)
{
	Elf *e;

	e = NULL;

	if (LIBELF_PRIVATE(version) == EV_NONE) {
		LIBELF_SET_ERROR(SEQUENCE, 0);
		return (NULL);
	}

	switch (c) {
	case ELF_C_NULL:
		return (NULL);

	case ELF_C_WRITE:
		/*
		 * The ELF_C_WRITE command is required to ignore the
		 * descriptor passed in.
		 */
		a = NULL;
		break;

	case ELF_C_RDWR:
		if (a != NULL) { /* not allowed for ar(1) archives. */
			LIBELF_SET_ERROR(ARGUMENT, 0);
			return (NULL);
		}
		/*FALLTHROUGH*/
	case ELF_C_READ:
		/*
		 * Descriptor `a' could be for a regular ELF file, or
		 * for an ar(1) archive.  If descriptor `a' was opened
		 * using a valid file descriptor, we need to check if
		 * the passed in `fd' value matches the original one.
		 */
		if (a &&
		    ((a->e_fd != -1 && a->e_fd != fd) || c != a->e_cmd)) {
			LIBELF_SET_ERROR(ARGUMENT, 0);
			return (NULL);
		}
		break;

	default:
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (NULL);

	}

	if (a == NULL)
		e = _libelf_open_object(fd, c, 1);
	else if (a->e_kind == ELF_K_AR)
		e = _libelf_ar_open_member(a->e_fd, c, a);
	else
		(e = a)->e_activations++;

	return (e);
}