#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {scalar_t__ st_shndx; int st_value; int /*<<< orphan*/  st_info; } ;
typedef  TYPE_1__ Elf_Internal_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_ST_BIND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ELF_ST_INFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ SHN_UNDEF ; 
 scalar_t__ STT_ARM_TFUNC ; 
 int /*<<< orphan*/  STT_FUNC ; 
 int /*<<< orphan*/  bfd_elf32_swap_symbol_out (int /*<<< orphan*/ *,TYPE_1__ const*,void*,void*) ; 

__attribute__((used)) static void
elf32_arm_swap_symbol_out (bfd *abfd,
			   const Elf_Internal_Sym *src,
			   void *cdst,
			   void *shndx)
{
  Elf_Internal_Sym newsym;

  /* We convert STT_ARM_TFUNC symbols into STT_FUNC with the low bit
     of the address set, as per the new EABI.  We do this unconditionally
     because objcopy does not set the elf header flags until after
     it writes out the symbol table.  */
  if (ELF_ST_TYPE (src->st_info) == STT_ARM_TFUNC)
    {
      newsym = *src;
      newsym.st_info = ELF_ST_INFO (ELF_ST_BIND (src->st_info), STT_FUNC);
      if (newsym.st_shndx != SHN_UNDEF)
        {
          /* Do this only for defined symbols. At link type, the static
             linker will simulate the work of dynamic linker of resolving
             symbols and will carry over the thumbness of found symbols to
             the output symbol table. It's not clear how it happens, but
             the thumbness of undefined symbols can well be different at
             runtime, and writing '1' for them will be confusing for users
             and possibly for dynamic linker itself.
          */
          newsym.st_value |= 1;
        }
      
      src = &newsym;
    }
  bfd_elf32_swap_symbol_out (abfd, src, cdst, shndx);
}