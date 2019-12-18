#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ e_kind; int e_class; scalar_t__ e_cmd; } ;
struct TYPE_12__ {int /*<<< orphan*/  e_shstrndx; int /*<<< orphan*/  e_shnum; int /*<<< orphan*/  e_shentsize; int /*<<< orphan*/  e_phnum; int /*<<< orphan*/  e_phentsize; int /*<<< orphan*/  e_ehsize; int /*<<< orphan*/  e_flags; int /*<<< orphan*/  e_version; int /*<<< orphan*/  e_machine; int /*<<< orphan*/  e_type; int /*<<< orphan*/  e_ident; } ;
struct TYPE_11__ {int /*<<< orphan*/  e_shstrndx; int /*<<< orphan*/  e_shnum; int /*<<< orphan*/  e_shentsize; int /*<<< orphan*/  e_phnum; int /*<<< orphan*/  e_phentsize; int /*<<< orphan*/  e_ehsize; int /*<<< orphan*/  e_flags; int /*<<< orphan*/  e_version; int /*<<< orphan*/  e_machine; int /*<<< orphan*/  e_type; int /*<<< orphan*/  e_ident; } ;
typedef  TYPE_1__ GElf_Ehdr ;
typedef  TYPE_1__ Elf64_Ehdr ;
typedef  TYPE_3__ Elf32_Ehdr ;
typedef  TYPE_4__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 int ELFCLASS32 ; 
 int ELFCLASS64 ; 
 scalar_t__ ELF_C_READ ; 
 int /*<<< orphan*/  ELF_C_SET ; 
 int /*<<< orphan*/  ELF_F_DIRTY ; 
 scalar_t__ ELF_K_ELF ; 
 int /*<<< orphan*/  LIBELF_COPY_U32 (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MODE ; 
 void* _libelf_ehdr (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_entry ; 
 int /*<<< orphan*/  e_phoff ; 
 int /*<<< orphan*/  e_shoff ; 
 int /*<<< orphan*/  elf_flagehdr (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
gelf_update_ehdr(Elf *e, GElf_Ehdr *s)
{
	int ec;
	void *ehdr;
	Elf32_Ehdr *eh32;
	Elf64_Ehdr *eh64;

	if (s== NULL || e == NULL || e->e_kind != ELF_K_ELF ||
	    ((ec = e->e_class) != ELFCLASS32 && ec != ELFCLASS64)) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (0);
	}

	if (e->e_cmd == ELF_C_READ) {
		LIBELF_SET_ERROR(MODE, 0);
		return (0);
	}

	if ((ehdr = _libelf_ehdr(e, ec, 0)) == NULL)
		return (0);

	(void) elf_flagehdr(e, ELF_C_SET, ELF_F_DIRTY);

	if (ec == ELFCLASS64) {
		eh64 = (Elf64_Ehdr *) ehdr;
		*eh64 = *s;
		return (1);
	}

	eh32 = (Elf32_Ehdr *) ehdr;

	(void) memcpy(eh32->e_ident, s->e_ident, sizeof(eh32->e_ident));

	eh32->e_type      = s->e_type;
	eh32->e_machine   = s->e_machine;
	eh32->e_version   = s->e_version;
	LIBELF_COPY_U32(eh32, s, e_entry);
	LIBELF_COPY_U32(eh32, s, e_phoff);
	LIBELF_COPY_U32(eh32, s, e_shoff);
	eh32->e_flags     = s->e_flags;
	eh32->e_ehsize    = s->e_ehsize;
	eh32->e_phentsize = s->e_phentsize;
	eh32->e_phnum     = s->e_phnum;
	eh32->e_shentsize = s->e_shentsize;
	eh32->e_shnum     = s->e_shnum;
	eh32->e_shstrndx  = s->e_shstrndx;

	return (1);
}