#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  e_scn; } ;
struct TYPE_15__ {TYPE_1__ e_elf; } ;
struct TYPE_17__ {scalar_t__ e_kind; int e_class; scalar_t__ e_cmd; int e_flags; TYPE_2__ e_u; } ;
struct TYPE_16__ {size_t s_ndx; } ;
typedef  TYPE_3__ Elf_Scn ;
typedef  TYPE_4__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 int ELFCLASS32 ; 
 int ELFCLASS64 ; 
 scalar_t__ ELF_C_WRITE ; 
 scalar_t__ ELF_K_ELF ; 
 int LIBELF_F_SHDRS_LOADED ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* RB_LEFT (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* RB_RIGHT (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* RB_ROOT (int /*<<< orphan*/ *) ; 
 void* _libelf_ehdr (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ _libelf_load_section_headers (TYPE_4__*,void*) ; 
 int /*<<< orphan*/  s_tree ; 

Elf_Scn *
elf_getscn(Elf *e, size_t index)
{
	int ec;
	void *ehdr;
	Elf_Scn *s;

	if (e == NULL || e->e_kind != ELF_K_ELF ||
	    ((ec = e->e_class) != ELFCLASS32 && ec != ELFCLASS64)) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (NULL);
	}

	if ((ehdr = _libelf_ehdr(e, ec, 0)) == NULL)
		return (NULL);

	if (e->e_cmd != ELF_C_WRITE &&
	    (e->e_flags & LIBELF_F_SHDRS_LOADED) == 0 &&
	    _libelf_load_section_headers(e, ehdr) == 0)
		return (NULL);

	for (s = RB_ROOT(&e->e_u.e_elf.e_scn); s != NULL;) {
		if (s->s_ndx == index)
			return (s);

		if (s->s_ndx < index)
			s = RB_RIGHT(s, s_tree);
		else
			s = RB_LEFT(s, s_tree);
	}

	LIBELF_SET_ERROR(ARGUMENT, 0);
	return (NULL);
}