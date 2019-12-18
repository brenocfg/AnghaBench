#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* e_ehdr64; } ;
struct TYPE_9__ {TYPE_2__ e_ehdr; } ;
struct TYPE_10__ {TYPE_3__ e_elf; } ;
struct TYPE_11__ {scalar_t__ e_kind; scalar_t__ e_class; TYPE_4__ e_u; } ;
struct TYPE_7__ {scalar_t__ e_machine; scalar_t__* e_ident; } ;
typedef  TYPE_5__ Elf ;

/* Variables and functions */
 size_t EI_DATA ; 
 scalar_t__ ELFCLASS64 ; 
 scalar_t__ ELFDATA2LSB ; 
 scalar_t__ ELF_K_ELF ; 
 scalar_t__ EM_MIPS ; 

int
_libelf_is_mips64el(Elf *e)
{

	return (e->e_kind == ELF_K_ELF && e->e_class == ELFCLASS64 &&
	    e->e_u.e_elf.e_ehdr.e_ehdr64->e_machine == EM_MIPS &&
	    e->e_u.e_elf.e_ehdr.e_ehdr64->e_ident[EI_DATA] == ELFDATA2LSB);
}