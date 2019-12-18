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
struct TYPE_5__ {int /*<<< orphan*/ * e_rawhdr; } ;
struct TYPE_6__ {int e_activations; int e_fd; int /*<<< orphan*/  e_u; int /*<<< orphan*/  e_version; scalar_t__ e_rawsize; int /*<<< orphan*/ * e_rawfile; int /*<<< orphan*/ * e_parent; int /*<<< orphan*/  e_kind; scalar_t__ e_flags; int /*<<< orphan*/  e_cmd; int /*<<< orphan*/  e_class; int /*<<< orphan*/  e_byteorder; TYPE_1__ e_hdr; } ;
typedef  TYPE_2__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ELFCLASSNONE ; 
 int /*<<< orphan*/  ELFDATANONE ; 
 int /*<<< orphan*/  ELF_C_NULL ; 
 int /*<<< orphan*/  ELF_K_NONE ; 
 int /*<<< orphan*/  LIBELF_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESOURCE ; 
 int /*<<< orphan*/  errno ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  version ; 

Elf *
_libelf_allocate_elf(void)
{
	Elf *e;

	if ((e = malloc(sizeof(*e))) == NULL) {
		LIBELF_SET_ERROR(RESOURCE, errno);
		return NULL;
	}

	e->e_activations = 1;
	e->e_hdr.e_rawhdr = NULL;
	e->e_byteorder   = ELFDATANONE;
	e->e_class       = ELFCLASSNONE;
	e->e_cmd         = ELF_C_NULL;
	e->e_fd          = -1;
	e->e_flags	 = 0;
	e->e_kind        = ELF_K_NONE;
	e->e_parent      = NULL;
	e->e_rawfile     = NULL;
	e->e_rawsize     = 0;
	e->e_version     = LIBELF_PRIVATE(version);

	(void) memset(&e->e_u, 0, sizeof(e->e_u));

	return (e);
}