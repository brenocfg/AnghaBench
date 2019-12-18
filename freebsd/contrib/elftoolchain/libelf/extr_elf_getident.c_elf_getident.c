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
struct TYPE_3__ {scalar_t__ e_cmd; scalar_t__ e_kind; size_t e_rawsize; int /*<<< orphan*/ * e_rawfile; } ;
typedef  TYPE_1__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 size_t EI_NIDENT ; 
 scalar_t__ ELF_C_READ ; 
 scalar_t__ ELF_C_WRITE ; 
 scalar_t__ ELF_K_AR ; 
 scalar_t__ ELF_K_ELF ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t SARMAG ; 
 int /*<<< orphan*/  SEQUENCE ; 
 int /*<<< orphan*/  assert (int) ; 

char *
elf_getident(Elf *e, size_t *sz)
{

	if (e == NULL) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		goto error;
	}

	if (e->e_cmd == ELF_C_WRITE && e->e_rawfile == NULL) {
		LIBELF_SET_ERROR(SEQUENCE, 0);
		goto error;
	}

	assert(e->e_kind != ELF_K_AR || e->e_cmd == ELF_C_READ);

	if (sz) {
		if (e->e_kind == ELF_K_AR)
			*sz = SARMAG;
		else if (e->e_kind == ELF_K_ELF)
			*sz = EI_NIDENT;
		else
			*sz = e->e_rawsize;
	}

	return ((char *) e->e_rawfile);

 error:
	if (sz)
		*sz = 0;
	return (NULL);
}