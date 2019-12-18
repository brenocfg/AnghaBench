#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_7__* e_arhdr; } ;
struct TYPE_14__ {int /*<<< orphan*/  e_phdr64; int /*<<< orphan*/  e_phdr32; } ;
struct TYPE_13__ {int /*<<< orphan*/  e_ehdr64; int /*<<< orphan*/  e_ehdr32; } ;
struct TYPE_15__ {int /*<<< orphan*/  e_scn; TYPE_3__ e_phdr; TYPE_2__ e_ehdr; } ;
struct TYPE_12__ {int /*<<< orphan*/  e_symtab; } ;
struct TYPE_16__ {TYPE_4__ e_elf; TYPE_1__ e_ar; } ;
struct TYPE_18__ {int e_kind; int e_flags; int /*<<< orphan*/  ar_rawname; int /*<<< orphan*/  ar_name; TYPE_6__ e_hdr; TYPE_5__ e_u; int /*<<< orphan*/  e_class; } ;
typedef  TYPE_7__ Elf_Arhdr ;
typedef  TYPE_7__ Elf ;

/* Variables and functions */
#define  ELFCLASS32 131 
#define  ELFCLASS64 130 
#define  ELF_K_AR 129 
#define  ELF_K_ELF 128 
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ) ; 
 int LIBELF_F_AR_HEADER ; 
 int /*<<< orphan*/  RB_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_7__*) ; 

Elf *
_libelf_release_elf(Elf *e)
{
	Elf_Arhdr *arh;

	switch (e->e_kind) {
	case ELF_K_AR:
		FREE(e->e_u.e_ar.e_symtab);
		break;

	case ELF_K_ELF:
		switch (e->e_class) {
		case ELFCLASS32:
			FREE(e->e_u.e_elf.e_ehdr.e_ehdr32);
			FREE(e->e_u.e_elf.e_phdr.e_phdr32);
			break;
		case ELFCLASS64:
			FREE(e->e_u.e_elf.e_ehdr.e_ehdr64);
			FREE(e->e_u.e_elf.e_phdr.e_phdr64);
			break;
		}

		assert(RB_EMPTY(&e->e_u.e_elf.e_scn));

		if (e->e_flags & LIBELF_F_AR_HEADER) {
			arh = e->e_hdr.e_arhdr;
			FREE(arh->ar_name);
			FREE(arh->ar_rawname);
			free(arh);
		}

		break;

	default:
		break;
	}

	free(e);

	return (NULL);
}