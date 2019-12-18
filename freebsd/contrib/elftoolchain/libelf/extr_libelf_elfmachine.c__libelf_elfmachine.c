#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_4__* e_ehdr64; TYPE_5__* e_ehdr32; } ;
struct TYPE_8__ {TYPE_2__ e_ehdr; } ;
struct TYPE_10__ {TYPE_1__ e_elf; } ;
struct TYPE_13__ {scalar_t__ e_kind; int e_class; TYPE_3__ e_u; } ;
struct TYPE_12__ {int e_machine; } ;
struct TYPE_11__ {int e_machine; } ;
typedef  TYPE_4__ Elf64_Ehdr ;
typedef  TYPE_5__ Elf32_Ehdr ;
typedef  TYPE_6__ Elf ;

/* Variables and functions */
#define  ELFCLASS32 129 
#define  ELFCLASS64 128 
 int ELFCLASSNONE ; 
 scalar_t__ ELF_K_ELF ; 
 int EM_NONE ; 
 int /*<<< orphan*/  assert (int) ; 

int
_libelf_elfmachine(Elf *e)
{
	Elf32_Ehdr *eh32;
	Elf64_Ehdr *eh64;

	if (!e)
		return EM_NONE;

	assert(e->e_kind == ELF_K_ELF);
	assert(e->e_class != ELFCLASSNONE);

	eh32 = NULL;
	eh64 = NULL;

	switch (e->e_class) {
	case ELFCLASS32:
		eh32 = e->e_u.e_elf.e_ehdr.e_ehdr32;
		return eh32 ? eh32->e_machine : EM_NONE;
	case ELFCLASS64:
		eh64 = e->e_u.e_elf.e_ehdr.e_ehdr64;
		return eh64 ? eh64->e_machine : EM_NONE;
	}

	return (EM_NONE);
}