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
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {int st_value; int /*<<< orphan*/  st_info; } ;
typedef  TYPE_1__ Elf_Internal_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_ST_BIND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ELF_ST_INFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  STT_ARM_TFUNC ; 
 scalar_t__ STT_FUNC ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_elf32_swap_symbol_in (int /*<<< orphan*/ *,void const*,void const*,TYPE_1__*) ; 

__attribute__((used)) static bfd_boolean
elf32_arm_swap_symbol_in (bfd * abfd,
			  const void *psrc,
			  const void *pshn,
			  Elf_Internal_Sym *dst)
{
  if (!bfd_elf32_swap_symbol_in (abfd, psrc, pshn, dst))
    return FALSE;

  /* New EABI objects mark thumb function symbols by setting the low bit of
     the address.  Turn these into STT_ARM_TFUNC.  */
  if (ELF_ST_TYPE (dst->st_info) == STT_FUNC
      && (dst->st_value & 1))
    {
      dst->st_info = ELF_ST_INFO (ELF_ST_BIND (dst->st_info), STT_ARM_TFUNC);
      dst->st_value &= ~(bfd_vma) 1;
    }
  return TRUE;
}