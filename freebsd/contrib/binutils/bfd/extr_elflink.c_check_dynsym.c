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
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_3__ {scalar_t__ st_shndx; } ;
typedef  TYPE_1__ Elf_Internal_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SHN_HIRESERVE ; 
 int /*<<< orphan*/  SHN_LORESERVE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_count_sections (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_error_nonrepresentable_section ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
check_dynsym (bfd *abfd, Elf_Internal_Sym *sym)
{
  if (sym->st_shndx > SHN_HIRESERVE)
    {
      /* The gABI doesn't support dynamic symbols in output sections
         beyond 64k.  */
      (*_bfd_error_handler)
	(_("%B: Too many sections: %d (>= %d)"),
	 abfd, bfd_count_sections (abfd), SHN_LORESERVE);
      bfd_set_error (bfd_error_nonrepresentable_section);
      return FALSE;
    }
  return TRUE;
}