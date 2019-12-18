#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_6__* e_phdr32; TYPE_4__* e_phdr64; } ;
struct TYPE_16__ {TYPE_1__ e_phdr; } ;
struct TYPE_17__ {TYPE_2__ e_elf; } ;
struct TYPE_20__ {scalar_t__ e_kind; int e_class; scalar_t__ e_cmd; TYPE_3__ e_u; } ;
struct TYPE_19__ {int /*<<< orphan*/  p_flags; int /*<<< orphan*/  p_type; } ;
struct TYPE_18__ {int /*<<< orphan*/  p_flags; int /*<<< orphan*/  p_type; } ;
typedef  TYPE_4__ GElf_Phdr ;
typedef  TYPE_4__ Elf64_Phdr ;
typedef  TYPE_6__ Elf32_Phdr ;
typedef  TYPE_7__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 int ELFCLASS32 ; 
 int ELFCLASS64 ; 
 scalar_t__ ELF_C_READ ; 
 int /*<<< orphan*/  ELF_C_SET ; 
 int /*<<< orphan*/  ELF_F_DIRTY ; 
 scalar_t__ ELF_K_ELF ; 
 int /*<<< orphan*/  LIBELF_COPY_U32 (TYPE_6__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MODE ; 
 void* _libelf_ehdr (TYPE_7__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elf_flagphdr (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ elf_getphdrnum (TYPE_7__*,size_t*) ; 
 int /*<<< orphan*/  p_align ; 
 int /*<<< orphan*/  p_filesz ; 
 int /*<<< orphan*/  p_memsz ; 
 int /*<<< orphan*/  p_offset ; 
 int /*<<< orphan*/  p_paddr ; 
 int /*<<< orphan*/  p_vaddr ; 

int
gelf_update_phdr(Elf *e, int ndx, GElf_Phdr *s)
{
	int ec;
	size_t phnum;
	void *ehdr;
	Elf32_Phdr *ph32;
	Elf64_Phdr *ph64;

	if (s == NULL || e == NULL || e->e_kind != ELF_K_ELF ||
	    ((ec = e->e_class) != ELFCLASS32 && ec != ELFCLASS64) ||
	    elf_getphdrnum(e, &phnum) < 0) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (0);
	}

	if (e->e_cmd == ELF_C_READ) {
		LIBELF_SET_ERROR(MODE, 0);
		return (0);
	}

	if ((ehdr = _libelf_ehdr(e, ec, 0)) == NULL)
		return (0);

	if (ndx < 0 || (size_t)ndx > phnum) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (0);
	}

	(void) elf_flagphdr(e, ELF_C_SET, ELF_F_DIRTY);

	if (ec == ELFCLASS64) {
		ph64 = e->e_u.e_elf.e_phdr.e_phdr64 + ndx;
		*ph64 = *s;
		return (1);
	}

	ph32 = e->e_u.e_elf.e_phdr.e_phdr32 + ndx;

	ph32->p_type     =  s->p_type;
	ph32->p_flags    =  s->p_flags;
	LIBELF_COPY_U32(ph32, s, p_offset);
	LIBELF_COPY_U32(ph32, s, p_vaddr);
	LIBELF_COPY_U32(ph32, s, p_paddr);
	LIBELF_COPY_U32(ph32, s, p_filesz);
	LIBELF_COPY_U32(ph32, s, p_memsz);
	LIBELF_COPY_U32(ph32, s, p_align);

	return (1);
}