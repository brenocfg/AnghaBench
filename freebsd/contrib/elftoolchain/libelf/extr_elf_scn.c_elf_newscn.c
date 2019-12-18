#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t e_nscn; int /*<<< orphan*/  e_scn; } ;
struct TYPE_9__ {TYPE_1__ e_elf; } ;
struct TYPE_10__ {scalar_t__ e_kind; int e_class; scalar_t__ e_cmd; int e_flags; TYPE_2__ e_u; } ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  TYPE_3__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 int /*<<< orphan*/  CLASS ; 
 int ELFCLASS32 ; 
 int ELFCLASS64 ; 
 int /*<<< orphan*/  ELF_C_SET ; 
 scalar_t__ ELF_C_WRITE ; 
 int /*<<< orphan*/  ELF_F_DIRTY ; 
 scalar_t__ ELF_K_ELF ; 
 int LIBELF_F_SHDRS_LOADED ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RB_EMPTY (int /*<<< orphan*/ *) ; 
 scalar_t__ SHN_UNDEF ; 
 int /*<<< orphan*/ * _libelf_allocate_scn (TYPE_3__*,size_t) ; 
 void* _libelf_ehdr (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ _libelf_load_section_headers (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  elf_flagscn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Elf_Scn *
elf_newscn(Elf *e)
{
	int ec;
	void *ehdr;
	Elf_Scn *scn;

	if (e == NULL || e->e_kind != ELF_K_ELF) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (NULL);
	}

	if ((ec = e->e_class) != ELFCLASS32 && ec != ELFCLASS64) {
		LIBELF_SET_ERROR(CLASS, 0);
		return (NULL);
	}

	if ((ehdr = _libelf_ehdr(e, ec, 0)) == NULL)
		return (NULL);

	/*
	 * The application may be asking for a new section descriptor
	 * on an ELF object opened with ELF_C_RDWR or ELF_C_READ.  We
	 * need to bring in the existing section information before
	 * appending a new one to the list.
	 *
	 * Per the ELF(3) API, an application is allowed to open a
	 * file using ELF_C_READ, mess with its internal structure and
	 * use elf_update(...,ELF_C_NULL) to compute its new layout.
	 */
	if (e->e_cmd != ELF_C_WRITE &&
	    (e->e_flags & LIBELF_F_SHDRS_LOADED) == 0 &&
	    _libelf_load_section_headers(e, ehdr) == 0)
		return (NULL);

	if (RB_EMPTY(&e->e_u.e_elf.e_scn)) {
		assert(e->e_u.e_elf.e_nscn == 0);
		if ((scn = _libelf_allocate_scn(e, (size_t) SHN_UNDEF)) ==
		    NULL)
			return (NULL);
		e->e_u.e_elf.e_nscn++;
	}

	assert(e->e_u.e_elf.e_nscn > 0);

	if ((scn = _libelf_allocate_scn(e, e->e_u.e_elf.e_nscn)) == NULL)
		return (NULL);

	e->e_u.e_elf.e_nscn++;

	(void) elf_flagscn(scn, ELF_C_SET, ELF_F_DIRTY);

	return (scn);
}