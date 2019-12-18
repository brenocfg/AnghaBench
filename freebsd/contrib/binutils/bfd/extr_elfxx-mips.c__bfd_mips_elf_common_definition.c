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
typedef  int bfd_boolean ;
struct TYPE_3__ {scalar_t__ st_shndx; } ;
typedef  TYPE_1__ Elf_Internal_Sym ;

/* Variables and functions */
 scalar_t__ SHN_COMMON ; 
 scalar_t__ SHN_MIPS_ACOMMON ; 
 scalar_t__ SHN_MIPS_SCOMMON ; 

bfd_boolean
_bfd_mips_elf_common_definition (Elf_Internal_Sym *sym)
{
  return (sym->st_shndx == SHN_COMMON
	  || sym->st_shndx == SHN_MIPS_ACOMMON
	  || sym->st_shndx == SHN_MIPS_SCOMMON);
}